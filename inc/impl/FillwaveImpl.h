/*
 * Fillwave.h
 *
 *  Created on: Nov 1, 2015
 *      Author: filip
 */

#ifndef FILLWAVE_INC_FILLWAVEIMPL_H_
#define FILLWAVE_INC_FILLWAVEIMPL_H_

#include <fillwave/Core.h>
#include <fillwave/Framework.h>

/* Extras */
#include <fillwave/Debugger.h>

/* Management */
#include <fillwave/management/ProgramManager.h>
#include <fillwave/management/ShaderManager.h>
#include <fillwave/management/SamplerManager.h>
#include <fillwave/management/BufferManager.h>
#include <fillwave/management/LightSystem.h>
#include <fillwave/management/TextureSystem.h>

#include <fillwave/common/Macros.h>
#include <fillwave/loaders/FileLoader.h>

FLOGINIT("Engine", FERROR | FFATAL | FDEBUG | FINFO)

struct ANativeActivity;
class Engine;

using namespace fillwave::framework;

namespace fillwave {

struct Engine::EngineImpl final {

#ifdef __ANDROID__
	EngineImpl(Engine* engine, std::string rootPath);
	EngineImpl(Engine* engine, ANativeActivity* activity);
#else
	EngineImpl(Engine* engine, GLint argc, GLchar* const argv[]);
#endif

	~EngineImpl();

	Engine* mEngine;

	/* Asset loader */
#ifdef FILLWAVE_COMPILATION_TINY_ASSET_LOADER
#else
	Assimp::Importer mImporter;
#endif

	/* Screen */
	GLuint mWindowWidth = 1920;
	GLuint mWindowHeight = 1200;
	GLfloat mWindowAspectRatio = 1200.0f / 1920.0f;

	/* Loaders */
	framework::FontLoader mFontLoader;
	framework::FileLoader mFileLoader;
	framework::ProgramLoader mProgramLoader;

	/* Scene */
	pIScene mScene;
	glm::vec3 mBackgroundColor;

	/* Picking */
	core::Texture2DRenderable* mPickingRenderableTexture;
	puPixelBuffer mPickingPixelBuffer;

	/* Resources */
	ManagerShaders mShaders;
	ManagerPrograms mPrograms;
	ManagerSamplers mSamplers;
	BufferManager mBuffers;
	std::vector<pText> mTextManager;
	std::vector<pFont> mFontManager;
	puLightSystem mLights;
	puTextureSystem mTextures;
	std::vector<core::PostProcessingPass> mPostProcessingPasses;
	pProgram mProgramTextureLookup;

	/* Fences and barriers */
	puFence mFence;

	/* OQ */
	pProgram mProgramOcclusionBox;
	puVertexBufferPosition mVBOOcclusion;
	pVertexArray mVAOOcclusion;

	/* Inputs - focus */
	std::map<eEventType, pEntity> mFocus;

	/* Inputs - callbacks */
	std::map<eEventType, std::vector<puCallback> > mCallbacks;

	/* Extras */
	puDebugger mDebugger;
	GLuint mFrameCounter;
	GLfloat mTimeFactor;
	pText mFPSText;
	framework::FPSCallback* mTextFPSCallback;

	/* Startup */
	GLfloat mStartupTime;
	core::Texture* mStartupTexture;
	const GLfloat mStartupTimeLimit = 8.0f;
	puPostProcessingPass mPostProcessingPassStartup;

	/* Options */
	GLboolean mIsOQ; /* Occlusion query */

	/* Callbacks */
	void runCallbacks();
	void runCallbacks(framework::EventType& eventType);
	void clearCallbacks();
	void clearCallbacks(eEventType eventType);
	void clearCallback(framework::Callback* callback);
	void registerCallback(
	    framework::Callback* callback);
	void unregisterCallback(
	    framework::Callback* callback);

	/* Evaluation */
	void evaluateShadowMaps();
	void evaluateDebugger();
	void evaluateDynamicTextures(GLfloat timeExpiredInSeconds);
	void evaluateTime(GLfloat timeExpiredInSeconds);
	void evaluateStartupAnimation(GLfloat time);

	/* Draw types */
	void draw(GLfloat time);
	void drawFront();
	void drawOcclusionPass();

#ifdef FILLWAVE_GLES_3_0
#else
	void drawLines(GLfloat time);

	void drawPoints(GLfloat time);
#endif

	void drawTexture(core::Texture* t, core::Program* p);
	void drawTexture(core::Texture* t);

	/* IRenderer */
	void drawClear();
	void drawHUD();
	void drawSceneStartup();

	void drawScene(GLfloat time);
	void drawSceneCore();

	/* Picking */
	glm::ivec4 pickingBufferGetColor(GLubyte* data, GLuint x, GLuint y);

	/* Initiatization */
	void init();
	void initExtensions();
	void initContext();
	void initPickingBuffer();
	void initPipelines();
	void initUniforms();
	void initManagement();
	void initExtras();
	void initOcclusionTest();
	void initStartup();

	/* Reload */
	void reload();
	void reloadPickingBuffer();

	/* Insert */
	void insertResizeScreen(GLuint width, GLuint height);
};

#ifdef __ANDROID__

Engine::EngineImpl::EngineImpl(Engine* engine, std::string rootPath)
	: mEngine(engine),
	  mFileLoader(rootPath),
	  mProgramLoader(engine),
	  mBackgroundColor(0.1, 0.1, 0.1),
	  mFrameCounter(0),
	  mTimeFactor(1.0),
	  mStartupTime(0.0f),
	  mIsOQ(GL_FALSE) {
//	init();
}

Engine::EngineImpl::EngineImpl(Engine* engine, ANativeActivity* activity)
	: mEngine(engine),
	  mFileLoader(activity->internalDataPath),
	  mProgramLoader(engine),
	  mBackgroundColor(0.1, 0.1, 0.1),
	  mFrameCounter(0),
	  mTimeFactor(1.0),
	  mStartupTime(0.0f),
	  mIsOQ(GL_FALSE) {

	androidSetActivity(activity);

	androidExtractAll();

#else
Engine::EngineImpl::EngineImpl(Engine* engine, GLint, GLchar* const argv[])
	: mEngine(engine),
	  mFileLoader(getFilePathOnly(argv[0])),
	  mProgramLoader(engine),
	  mBackgroundColor(0.1, 0.1, 0.1),
	  mShaders(),
	  mFrameCounter(0),
	  mTimeFactor(1.0),
	  mStartupTime(0.0f),
	  mIsOQ(GL_TRUE) {
#endif
//	init();
}

Engine::EngineImpl::~EngineImpl() {
	if (mScene) {
		mScene.reset();
	}
	mTextManager.clear();
	mFontManager.clear();
	mPostProcessingPasses.clear();
}

void Engine::EngineImpl::init() {

	initExtensions();
	initContext();
	initManagement();
	initPipelines();
	initUniforms();
	initPickingBuffer();
	initOcclusionTest();
	initExtras();

#ifdef FILLWAVE_COMPILATION_STARTUP_ANIMATION
	initStartup(engine);
#endif
//   mFence = puFence(new core::Fence());
}

#ifdef FILLWAVE_GLES_3_0

inline void Engine::EngineImpl::initExtensions() {
	glesInitExtensions();
}

#else

inline void Engine::EngineImpl::initExtensions(void) {
#ifdef GLEW_OK
	GLenum GlewInitResult;
	glewExperimental = GL_TRUE;

	GlewInitResult = glewInit();
	if (GL_NO_ERROR != glGetError()) {
		FLOG_ERROR("glewInit returned INVALID_ENUM ... It may happen");
	}

	if (GLEW_OK != GlewInitResult) {
		FLOG_ERROR("GLEW init failed. Error: %d", GlewInitResult);
		exit(EXIT_FAILURE);
	} else {
		FLOG_DEBUG("OpenGL Version: %s", glGetString(GL_VERSION));
	}

#endif
}

#endif

inline void Engine::EngineImpl::initManagement() {
	mTextures = make_unique<framework::TextureSystem>(mFileLoader.getRootPath());
	mLights = make_unique<framework::LightSystem>();
}

inline void Engine::EngineImpl::initPipelines() {
	/* OT */
	mProgramOcclusionBox = mProgramLoader.getOcclusionOptimizedQuery();

	/* T */
	mProgramTextureLookup = mProgramLoader.getQuad();
}

inline void Engine::EngineImpl::initUniforms() {
	mProgramTextureLookup->use();
	mProgramTextureLookup->uniformPush("uPostProcessingSampler",
	                                   FILLWAVE_DIFFUSE_UNIT);
	core::Program::disusePrograms();
}

inline void Engine::EngineImpl::initOcclusionTest() {
	std::vector<core::VertexPosition> vec = framework::BoxOcclusion().getVertices();
	mVAOOcclusion = mBuffers.getVAO(nullptr);
	mVBOOcclusion = puVertexBufferPosition(new core::VertexBufferPosition(vec));
	mVBOOcclusion->getAttributes(mProgramOcclusionBox->getHandle());
	mVBOOcclusion->attributesBind(mProgramOcclusionBox);
	mVAOOcclusion->bind();
	mVBOOcclusion->bind();
	mVBOOcclusion->attributesSetForVAO();
	mVBOOcclusion->send();
	core::VertexArray::unbindVAO();
}

inline void Engine::EngineImpl::initStartup() {

	pProgram program = mProgramLoader.getQuadCustomFragmentShaderStartup();

	program->use();
	program->uniformPush("uPostProcessingSampler", FILLWAVE_DIFFUSE_UNIT);
	program->uniformPush("uScreenFactor", mWindowAspectRatio);
	core::Program::disusePrograms();

	mPostProcessingPassStartup = make_unique<core::PostProcessingPass>(program,
	                             mTextures->getDynamic("fillwave_quad_startup.frag",
	                                     program, glm::ivec2(mWindowWidth, mWindowHeight)),
	                             mStartupTimeLimit);

	FLOG_DEBUG("Post processing startup pass added");

	mStartupTexture = mTextures->get("logo.png", framework::eCompression::eNone);
	if (not mStartupTexture) {
		mStartupTexture = mTextures->get("textures/logo.png",
		                                 framework::eCompression::eNone);
		if (not mStartupTexture) {
			mStartupTexture = mTextures->get("64_64_64.color",
			                                 framework::eCompression::eNone);
			FLOG_ERROR("Fillwave startup logo could not be executed");
		}
	}
}

inline void Engine::EngineImpl::initPickingBuffer() {
	mPickingPixelBuffer = puPixelBuffer(new core::PixelBuffer(GL_STREAM_READ));
	reloadPickingBuffer();
}

inline void Engine::EngineImpl::initExtras() {
	/* FPS counter */
	mTextFPSCallback = NULL;

	/* Debugger */
	mDebugger = make_unique<framework::Debugger>(mEngine);
}

void Engine::EngineImpl::reload() {

	initContext();

	for (auto& it : mShaders) {
		it.second->mComponent->reload();
	}

	for (auto& it : mPrograms) {
		it.second->mComponent->reload();
	}

	mTextures->reload();

	for (auto& it : mSamplers) {
		it.second->mComponent->reload();
	}

	mBuffers.reload();

	mPickingPixelBuffer->reload();
	reloadPickingBuffer();

//	mScene->resetRenderer(); xxx
}

inline void Engine::EngineImpl::reloadPickingBuffer() {
	mPickingRenderableTexture = mTextures->getColor2D(mWindowWidth,
	                            mWindowHeight);

	mPickingPixelBuffer->setScreenSize(mWindowWidth, mWindowHeight, 4);
	mPickingPixelBuffer->bind();
	mPickingPixelBuffer->setReady();
	mPickingPixelBuffer->send();
	glReadPixels(0, 0, mWindowWidth, mWindowHeight,
	             GL_RGBA,
	             GL_UNSIGNED_BYTE, 0);
	FLOG_CHECK("glReadPixels");
	mPickingPixelBuffer->unbind();
}

inline void Engine::EngineImpl::initContext(void) {
	glClearColor(mBackgroundColor.x, mBackgroundColor.y, mBackgroundColor.z,
	             1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	FLOG_CHECK("Could not set OpenGL depth testing options");
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	FLOG_CHECK("Could not set OpenGL culling options");
}

void Engine::EngineImpl::draw(GLfloat time) {
#ifdef FILLWAVE_COMPILATION_STARTUP_ANIMATION
	/* Draw startup animation */
	if (mStartupTime < mStartupTimeLimit) {
		evaluateStartupAnimation(time);
		mStartupTime += time;
		return;
	}
#endif

	if (mScene) {
		/* count this frame */
		mFrameCounter++;

		/* Clear main framebuffer */
		glClearDepth(1.0f);

		/* Calculate dynamic textures */
		mTextures->evaluateDynamicTextures(time);

		/* Lights evaluation */
		glDepthMask(GL_TRUE);
		evaluateShadowMaps();
		drawScene(time);
		drawFront();
	}
}

inline void Engine::EngineImpl::drawFront() {
	drawHUD();
	evaluateDebugger();
	mScene->drawCursor();
	mScene->updateDependencies();
	mScene->updateRenderer();
}

#ifdef FILLWAVE_GLES_3_0
#else
void Engine::EngineImpl::drawLines(GLfloat time) {

#ifdef FILLWAVE_COMPILATION_STARTUP_ANIMATION
	/* Draw startup animation */
	if (mStartupTime < mStartupTimeLimit) {
		evaluateStartupAnimation(time);
		mStartupTime += time;
		return;
	}
#endif

	/* count this frame */
	mFrameCounter++;

	/* clear main framebuffer */
	glClearDepth(1.0f);

	/* Calculate dynamic textures */
	mTextures->evaluateDynamicTextures(time);

	/* Lights evaluation */
	if (mScene) {
		evaluateShadowMaps();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		drawScene(time);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		drawFront();
	}
}

void Engine::EngineImpl::drawPoints(GLfloat time) {

#ifdef FILLWAVE_COMPILATION_STARTUP_ANIMATION
	/* Draw startup animation */
	if (mStartupTime < mStartupTimeLimit) {
		evaluateStartupAnimation(time);
		mStartupTime += time;
		return;
	}
#endif

	/* count this frame */
	mFrameCounter++;

	/* clear main framebuffer */
	glClearDepth(1.0f);

	/* Calculate dynamic textures */
	mTextures->evaluateDynamicTextures(time);

	/* Lights evaluation */
	if (mScene) {
		evaluateShadowMaps();
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		drawScene(time);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		drawFront();
	}
}
#endif

inline void Engine::EngineImpl::drawHUD() {
	if (mScene) {
		mScene->drawHUD();
	}
	for (auto& it : mTextManager) {
		it->draw();
	}
}

void Engine::EngineImpl::drawTexture(core::Texture* t, core::Program* p) {
	p->use();
	t->bind(FILLWAVE_DIFFUSE_UNIT);
	p->uniformPush("uPostProcessingSampler", FILLWAVE_DIFFUSE_UNIT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	t->unbind();
	core::Program::disusePrograms();
}

void Engine::EngineImpl::drawTexture(core::Texture* t) {
	mProgramTextureLookup->use();
	mProgramTextureLookup->uniformPush("uPostProcessingSampler",
	                                   FILLWAVE_DIFFUSE_UNIT);
	t->bind(FILLWAVE_DIFFUSE_UNIT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	t->unbind();
}

inline void Engine::EngineImpl::drawClear() {
	glClearColor(mBackgroundColor.x, mBackgroundColor.y, mBackgroundColor.z,
	             1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

inline void Engine::EngineImpl::drawScene(GLfloat time) {

	evaluateTime(time);

	if (mPostProcessingPasses.size()) {
		auto _compare_function =
		    [](core::PostProcessingPass & pass) -> bool {return pass.isFinished();};
		auto _begin = mPostProcessingPasses.begin();
		auto _end = mPostProcessingPasses.end();

		core::Texture2DRenderableDynamic* textureNext;
		core::Texture2DRenderableDynamic* textureCurrent = (*_begin).getFrame();

		core::Program* programCurrent;

		drawClear();
		textureCurrent->bindForWriting();
		drawSceneCore();

		for (auto it = _begin; it != _end; it++) {

			auto next = it + 1;

			if (next != _end) {

				textureNext = (*next).getFrame();
				textureCurrent = (*it).getFrame();
				programCurrent = (*it).getProgram().get();

				textureNext->bindForWriting();

				drawClear();

				textureCurrent->draw(0.0f);

				textureNext->draw(time);

				textureNext->bindForReading();

			} else {

				core::Framebuffer::bindScreenFramebuffer();

				// render to current bound framebuffer using textureCurrent as a texture to post process
				textureCurrent->draw(time);

				textureCurrent = (*it).getFrame();
				programCurrent = (*it).getProgram().get();

				// render to current bound framebuffer using textureCurrent as a texture to post process
				drawTexture(textureCurrent, programCurrent);
			}

			(*it).checkTime(time);
		}

		auto it = std::remove_if(_begin, _end, _compare_function);

		mPostProcessingPasses.erase(it, _end);

	} else {
		drawSceneCore();
	}
}

inline void Engine::EngineImpl::drawSceneCore() {
	if (mIsOQ) {
		drawOcclusionPass();
	}
	drawClear();
	mScene->draw();
}

inline void Engine::EngineImpl::drawOcclusionPass() {
	mVAOOcclusion->bind();

	glDisable(GL_CULL_FACE);
	glDepthMask(GL_FALSE);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	mScene->drawOcclusion();

	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	core::VertexArray::unbindVAO();
}

inline void Engine::EngineImpl::evaluateStartupAnimation(GLfloat time) {

	drawClear();

	core::Texture2DRenderableDynamic* t = mPostProcessingPassStartup->getFrame();

	t->bindForWriting();

	drawTexture(mStartupTexture);

	core::Framebuffer::bindScreenFramebuffer();

	t->draw(time);

	drawTexture(t, mPostProcessingPassStartup->getProgram().get());

	mPostProcessingPassStartup->checkTime(time);
}

inline void Engine::EngineImpl::evaluateShadowMaps() {

	glDepthMask(GL_TRUE);

	mLights->updateLightEntities();

	GLint currentTextureUnit = FILLWAVE_SHADOW_FIRST_UNIT;

	core::Texture2DRenderable* light2DTexture;
	for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
		light2DTexture = mLights->mLightsSpot[i]->getShadowTexture();
		light2DTexture->bindForWriting();
		light2DTexture->bind(currentTextureUnit++);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_DEPTH_BUFFER_BIT);
		mScene->drawDepth(*(mLights->mLightsSpot[i]->getShadowCamera().get()));
	}

	for (size_t i = 0; i < mLights->mLightsDirectional.size(); i++) {
		light2DTexture =
		    mLights->mLightsDirectional[i]->getShadowTexture();
		light2DTexture->bindForWriting();
		light2DTexture->bind(currentTextureUnit++);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_DEPTH_BUFFER_BIT);
		mScene->drawDepth(*(mLights->mLightsDirectional[i]->getShadowCamera().get()));
	}

	for (size_t i = 0; i < mLights->mLightsPoint.size(); i++) {
		framework::LightPoint* lightPoint = mLights->mLightsPoint[i].get();
		core::Texture3DRenderable* light3DTexture =
		    lightPoint->getShadowTexture();
		glm::vec3 lightPosition(lightPoint->getTranslation());
		light3DTexture->bindForWriting();
		light3DTexture->bind(currentTextureUnit);
		for (GLint j = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
		        j <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; j++) {
			light3DTexture->setAttachmentFace(j, GL_COLOR_ATTACHMENT0);
			glClearColor(0.0, 0.0, 0.0, 1.0);
			glClear(GL_DEPTH_BUFFER_BIT);
			mScene->drawDepthColor(*(lightPoint->getShadowCamera(j).get()), lightPosition);
		}
		currentTextureUnit++;
	}
	core::Framebuffer::bindScreenFramebuffer();
}

inline void Engine::EngineImpl::evaluateTime(GLfloat timeExpiredInSeconds) {
	if (mTimeFactor) {
		framework::TimeEventData data;
		data.mTimePassed = timeExpiredInSeconds;
		framework::TimeEvent timeEvent(data);
		runCallbacks(timeEvent);
		mScene->onEvent(timeEvent);
	}
}

inline void Engine::EngineImpl::evaluateDebugger() {
	GLint mCurentTextureUnit = 0;
	GLint id = 0;
	switch (mDebugger->getState()) {
	case eDebuggerState::eLightsSpot:
		mCurentTextureUnit = 0;
		for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
			framework::CameraPerspective cameraP =
			    *(mLights->mLightsSpot[i]->getShadowCamera().get());
			mDebugger->renderFromCamera(cameraP,
			                            mCurentTextureUnit++); //xxx make more flexible
		}
		for (size_t i = 0; i < mLights->mLightsDirectional.size();
		        i++) {
			framework::CameraOrthographic cameraO =
			    *(mLights->mLightsDirectional[i]->getShadowCamera().get());
			mDebugger->renderFromCamera(cameraO,
			                            mCurentTextureUnit++); //xxx make more flexible
		}
		mCurentTextureUnit = 0;
		for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
			mDebugger->renderDepthPerspective(mCurentTextureUnit++);
		}
		for (size_t i = 0; i < mLights->mLightsDirectional.size();
		        i++) {
			mDebugger->renderDepthOrthographic(mCurentTextureUnit++);
		}
		break;
	case eDebuggerState::eLightsSpotDepth:
		mCurentTextureUnit = 0;
		for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
			mDebugger->renderDepthPerspective(mCurentTextureUnit++);
		}
		for (size_t i = 0; i < mLights->mLightsDirectional.size();
		        i++) {
			mDebugger->renderDepthOrthographic(mCurentTextureUnit++);
		}
		break;
	case eDebuggerState::eLightsSpotColor:
		mCurentTextureUnit = 0;
		for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
			framework::CameraPerspective cameraP =
			    *(mLights->mLightsSpot[i]->getShadowCamera().get());
			mDebugger->renderFromCamera(cameraP,
			                            mCurentTextureUnit++); //xxx make more flexible
		}
		for (size_t i = 0; i < mLights->mLightsDirectional.size();
		        i++) {
			framework::CameraOrthographic cameraO =
			    *(mLights->mLightsDirectional[i]->getShadowCamera().get());
			mDebugger->renderFromCamera(cameraO,
			                            mCurentTextureUnit++); //xxx make more flexible
		}
		break;
	case eDebuggerState::eLightsPoint:
		break;
	case eDebuggerState::eLightsPointDepth: // only light 0
		break;
	case eDebuggerState::eLightsPointColor:
		for (size_t j = 0; j < mLights->mLightsPoint.size(); j++) {
			for (int i = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
			        i <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; i++) {
				framework::CameraPerspective cameraPF =
				    *(mLights->mLightsPoint[j]->getShadowCamera(i).get());
				mDebugger->renderFromCamera(cameraPF, id++);
			}
		}
		break;
	case eDebuggerState::ePickingMap:
		mDebugger->renderPickingMap();
		break;
	case eDebuggerState::eOff:
	default:
		break;
	}
}

void Engine::EngineImpl::runCallbacks(
    framework::EventType& event) {
	if (mCallbacks.find(event.getType()) != mCallbacks.end()) {
		for (auto& callback : mCallbacks[event.getType()]) {
			callback->perform(event);
		}
	}
}

void Engine::EngineImpl::insertResizeScreen(GLuint width, GLuint height) {

	mWindowWidth = width;
	mWindowHeight = height;
	mWindowAspectRatio = static_cast<GLfloat>(mWindowHeight) / static_cast<GLfloat>
	                     (mWindowWidth);

	glViewport(0, 0, mWindowWidth, mWindowHeight);

	mTextures->resize(mWindowWidth, mWindowHeight);
	mPickingPixelBuffer->setScreenSize(mWindowWidth, mWindowHeight, 4);
}

/* Callbacks */

void Engine::EngineImpl::registerCallback(
    framework::Callback* callback) {
	mCallbacks[callback->getEventType()].push_back(puCallback(callback));
}

void Engine::EngineImpl::unregisterCallback(
    framework::Callback* callback) {
	if (mCallbacks.find(callback->getEventType()) != mCallbacks.end()) {
		std::vector<puCallback>* callbacks = &mCallbacks[callback->getEventType()];
		auto _compare_function =
		    [callback](const puCallback & c) -> bool {bool found = (c.get() == callback); return found;};
		auto _begin = callbacks->begin();
		auto _end = callbacks->end();
		auto it = std::remove_if(_begin, _end, _compare_function);
		callbacks->erase(it, _end);
	}
}

glm::ivec4 Engine::EngineImpl::pickingBufferGetColor(
    GLubyte* data,
    GLuint x,
    GLuint y) {
	y = mWindowHeight - y;
	GLuint id, r, g, b, a;

	if (x < mWindowWidth && y < mWindowHeight) {
		id = (x + y * mWindowWidth) * 4;
		b = data[id];
		g = data[id + 1];
		r = data[id + 2];
		a = data[id + 3];
	}
	return glm::ivec4(r, g, b, a);
}

/* Engine callbacks - clear */

inline void Engine::EngineImpl::clearCallbacks() {
	mCallbacks.clear();
}

inline void Engine::EngineImpl::clearCallbacks(
    eEventType eventType) {
	if (mCallbacks.find(eventType) != mCallbacks.end()) {
		mCallbacks[eventType].clear();
	}
}

void Engine::EngineImpl::clearCallback(framework::Callback* callback) {
	eEventType e = callback->getEventType();
	std::vector<puCallback>* callbacks = &mCallbacks[e];
	callbacks->erase(
	    std::remove_if( // Selectively remove elements in the second vector...
	        callbacks->begin(),
	        callbacks->end(),
	[&] (puCallback const & p) {
		// This predicate checks whether the element is contained
		// in the second vector of pointers to be removed...
		return callback == p.get();
	}),
	callbacks->end()
	);
}

} /* fillwave */

#endif /* EXT_FILLWAVE_INC_FILLWAVEIMPL_H_ */
