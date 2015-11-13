/*
 * Fillwave.h
 *
 *  Created on: Nov 1, 2015
 *      Author: filip
 */

#ifndef FILLWAVE_INC_FILLWAVEIMPL_H_
#define FILLWAVE_INC_FILLWAVEIMPL_H_

/* Plarform specific */
#include <fillwave/loaders/AndroidLoader.h>

/* core */
#include <fillwave/core/rendering/FramebufferGeometry.h>
#include <fillwave/core/rendering/Texture2DRenderableDynamic.h>
#include <fillwave/core/buffers/PixelBuffer.h>

/* models */
#include <fillwave/models/BuilderModelManual.h>
#include <fillwave/models/BuilderModelExternalMaps.h>
#include <fillwave/models/SceneOrthographic.h>
#include <fillwave/models/ScenePerspective.h>
#include <fillwave/models/Text.h>
#include <fillwave/models/Skybox.h>
#include <fillwave/models/shapes/BoxOcclusion.h>
#include <fillwave/models/shapes/Box.h>

/* space */
#include <fillwave/space/LightPoint.h>
#include <fillwave/space/LightSpot.h>
#include <fillwave/space/LightDirectional.h>

/* Events */
#include <fillwave/actions/ItemCallback.h>
#include <fillwave/actions/TimeEvent.h>
#include <fillwave/actions/TouchEvent.h>
#include <fillwave/actions/ScrollEvent.h>
#include <fillwave/actions/CursorEnterEvent.h>
#include <fillwave/actions/CursorPositionEvent.h>
#include <fillwave/actions/CharacterEvent.h>
#include <fillwave/actions/CharacterModsEvent.h>
#include <fillwave/actions/CursorPositionEvent.h>
#include <fillwave/actions/MouseButtonEvent.h>
#include <fillwave/actions/KeyboardEvent.h>

/* Callbacks */
#include <fillwave/actions/FPSCallback.h>
#include <fillwave/actions/EngineCallback.h>
#include <fillwave/actions/TimedMoveCallback.h>
#include <fillwave/actions/TimedRotateCallback.h>
#include <fillwave/actions/TimedScaleCallback.h>
#include <fillwave/actions/TimedCallback.h>
#include <fillwave/actions/TimedEmiterUpdateCallback.h>
#include <fillwave/actions/LoopCallback.h>
#include <fillwave/actions/SequenceCallback.h>

/* Loaders */
#include <fillwave/loaders/FileLoader.h>

/* Extras */
#include <fillwave/extras/Debugger.h>

/* Operations */
#include <fillwave/core/operations/PostProcessingPass.h>

/* Common */
#include <fillwave/common/PhysicsMeshBuffer.h>

/* Management */
#include <fillwave/management/ProgramManager.h>
#include <fillwave/management/TextureManager.h>
#include <fillwave/management/ShaderManager.h>
#include <fillwave/management/LightManager.h>
#include <fillwave/management/SamplerManager.h>
#include <fillwave/management/BufferManager.h>

FLOGINIT("Engine", FERROR | FFATAL | FDEBUG | FINFO)

struct ANativeActivity;
class Engine;

using namespace fillwave::loader;

namespace fillwave {

struct Engine::EngineImpl {

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

	static const GLuint mDeferredColorAttachments = 4;
	static const GLuint mDeferredDepthAttachments = 1;

	/* Screen */
	GLuint mWindowWidth = 1920;
	GLuint mWindowHeight = 1200;

	/* Loaders */
	loader::FontLoader mFontLoader;
	loader::FileLoader mFileLoader;
	loader::ProgramLoader mProgramLoader;

	/* Scene */
	pScene mScene;
	glm::vec3 mBackgroundColor;

	/* Picking */
	pTexture2DRenderable mPickingRenderableTexture;
	puPixelBuffer mPickingPixelBuffer;

	/* Resources */
	puProgramManager mProgramManager;
	puTextureManager mTextureManager;
	puShaderManager mShaderManager;
	puLightManager mLightManager;
	puSamplerManager mSamplerManager;
	puBufferManager mBufferManager;
	std::vector<pText> mTextManager;
	std::vector<pFont> mFontManager;
	std::vector<common::PostProcessingPass> mPostProcessingPasses;
	std::vector<pTexture2DRenderableDynamic> mTexturesDynamic;
	pProgram mProgramTextureLookup;

	/* Fences and barriers */
	puFence mFence;

	/* DR - Deferred rendering */
	puFramebufferGeometry mGBuffer;

	/* ULC - Uniform location cache */
	pProgram mProgramDRSpotLight, mProgramDRDirecionalLight,
			mProgramDRPointLight, mProgramDRDepthless, mProgramDRAmbient;

	GLint mULCCameraPositionSpot, mULCAmbientIntensitySpot, mULCScreenSizeSpot,
			mULCShadowUnitSpot, mULCIsAOSpot;

	GLint mULCCameraPositionDirectional, mULCAmbientIntensityDirectional,
			mULCScreenSizeDirectional, mULCShadowUnitDirectional,
			mULCIsAODirectional;

	GLint mULCCameraPositionPoint, mULCAmbientIntensityPoint, mULCMVPPoint,
			mULCScreenSizePoint, mULCShadowUnitPoint, mULCIsAOPoint;

	GLint mULCDRDepthlesDiffuseTexel, mULCDRDepthlessPositionTexel,
			mULCDRScreenSize, uULCDRAScreenSize, uULCDRADiffuseAttachment,
			uULCDRAAmbientGlobal;

	puMesh mDeferredPointLight;

	/* AO */
	pProgram mProgramAOGeometry;
	pProgram mProgramAOColor;

	pTexture2DRenderable mAOGeometryBuffer;
	pTexture2DRenderable mAOColorBuffer;

	/* OQ */
	pProgram mProgramOcclusionBox;
	puVertexBufferPosition mVBOOcclusion;
	pVertexArray mVAOOcclusion;

	/* Inputs - focus */
	pEntity mFocusKey;
	pEntity mFocusMouseButton;
	pEntity mFocusScroll;
	pEntity mFocusChar;
	pEntity mFocusCharMods;
	pEntity mFocusCursorEnter;
	pEntity mFocusCursorPosition;
	pEntity mFocusTouchScreen;

	/* Inputs - callbacks */
	std::vector<actions::EngineCallback*> mTimeCallbacks;
	std::vector<actions::EngineCallback*> mKeyCallbacks;
	std::vector<actions::EngineCallback*> mMouseButtonCallbacks;
	std::vector<actions::EngineCallback*> mScrollCallbacks;
	std::vector<actions::EngineCallback*> mCharCallbacks;
	std::vector<actions::EngineCallback*> mCharModsCallbacks;
	std::vector<actions::EngineCallback*> mCursorEnterCallbacks;
	std::vector<actions::EngineCallback*> mCursorPositionCallbacks;
	std::vector<actions::EngineCallback*> mTouchScreenCallbacks;

	/* Extras */
	puDebugger mDebugger;
	GLuint mFrameCounter;
	GLfloat mTimeFactor;
	pText mFPSText;
	actions::FPSCallback* mTextFPSCallback;

	/* Startup */
	GLfloat mStartupTime;
	pTexture mStartupTexture;
	const GLfloat mStartupTimeLimit = 8.0f;
	puPostProcessingPass mPostProcessingPassStartup;

	/* Options */
	GLboolean mIsDR; /* Deferred rendering */
	GLboolean mIsAO; /* Ambient occlusion */
	GLboolean mISOQ; /* Occlusion query */

	/* Callbacks */
	void runCallbacks(
			std::vector<actions::EngineCallback*>& callbacks,
			actions::EventType* event);
	void clearCallbacks(std::vector<actions::EngineCallback*>& callbacks);
	void unregisterCallback(
			std::vector<actions::EngineCallback*>& callbacks,
			actions::EngineCallback* callback);

	/* Evaluation */
	void evaluateShadowMaps();

	void evaluateDebugger();

	void evaluateDynamicTextures(GLfloat timeExpiredInSeconds);

	void evaluateTime(GLfloat timeExpiredInSeconds);

	void evaluateStartupAnimation(GLfloat time);

	/* Draw types */

	void draw(GLfloat time);

#ifdef __ANDROID__

#else
	void drawLines(GLfloat time);

	void drawPoints(GLfloat time);
#endif

	void drawTexture(core::Texture* t, core::Program* p);

	void drawTexture(core::Texture* t);

	/* Draw passes */

	void drawClear();

	void drawScene(GLfloat time);

	void drawSceneStartup();

	void drawSceneCore();

	void drawSceneCoreFR();

	void drawSceneCoreDR();

	void drawText();

	void drawGeometryPass();

	void drawOcclusionPass();

	void drawDepthlessPass();

	void drawAmbientPass();

	void drawAOPass();

	void drawColorPass();

	void drawLightsSpotPass(GLint& textureUnit);

	void drawLightsDirectionalPass(GLint& textureUnit);

	void drawLightsPointPass(GLint& textureUnit);

	void drawColorPassBegin();

	void drawColorPassEnd();

	/* Store */

	pShader storeShader(const std::string& shaderPath, const GLuint& shaderType);

	pShader storeShader(
			const std::string& shaderName,
			const GLuint& shaderType,
			const std::string& shaderSource);

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

	void initDeferredShading();

	void initAmbientOcclusion();

	void initGeometryBuffer();

	void initExtras();

	void initOcclusionTest();

	void initUniformsCache();

	void initStartup();

	void initGeometryShading();

	/* Reload */
	void reload();

	void reloadPickingBuffer();

	void reloadGeometryBuffer();

	/* Insert */

	void insertResizeScreen(GLuint width, GLuint height);

	/* Store */

	pSampler storeSO(GLint textureUnit);

	pVertexArray storeVAO(models::Reloadable* user = nullptr);
};

#ifdef __ANDROID__

Engine::EngineImpl::EngineImpl(Engine* engine, std::string rootPath)
:mEngine(engine),
mFileLoader(rootPath),
mBackgroundColor(0.1,0.1,0.1),
mFrameCounter(0),
mTimeFactor(1.0),
mStartupTime(0.0f),
mIsDR(GL_FALSE),
mIsAO(GL_FALSE),
mISOQ(GL_FALSE) {
	init();
}

Engine::EngineImpl::EngineImpl(Engine* engine, ANativeActivity* activity)
:mEngine(engine),
mFileLoader(activity->internalDataPath),
mBackgroundColor(0.1,0.1,0.1),
mFrameCounter(0),
mTimeFactor(1.0),
mStartupTime(0.0f),
mIsDR(GL_FALSE),
mIsAO(GL_FALSE),
mISOQ(GL_FALSE) {

	androidSetActivity(activity);

	androidExtractAll();

#else
Engine::EngineImpl::EngineImpl(Engine* engine, GLint, GLchar* const argv[])
		:
				mEngine(engine),
				mFileLoader(strings::getFilePathOnly(argv[0])),
				mBackgroundColor(0.1,0.1,0.1),
				mFrameCounter(0),
				mTimeFactor(1.0),
				mStartupTime(0.0f),
				mIsDR(GL_FALSE),
				mIsAO(GL_FALSE),
				mISOQ(GL_TRUE) {
#endif
	init();
}

Engine::EngineImpl::~EngineImpl() {
	mTextManager.clear();
	mFontManager.clear();
	mPostProcessingPasses.clear();
	mTexturesDynamic.clear();
	if (mScene) {
		mScene.reset();
	}
}

inline void Engine::EngineImpl::init() {
	initExtensions();

	initContext();

	initManagement();

	initPipelines();

	initUniforms();

	initPickingBuffer();

	initOcclusionTest();

	initGeometryBuffer();

	initDeferredShading();

	initAmbientOcclusion();

	initExtras();

	initUniformsCache();

#ifdef __ANDROID__

#else
	initGeometryShading();
#endif

#ifdef FILLWAVE_COMPILATION_STARTUP_ANIMATION
	initStartup(engine);
#endif
//   mFence = puFence(new core::Fence());
}

#ifdef __ANDROID__

inline void Engine::EngineImpl::initExtensions() {
	glesInitExtensions();
}

#else

inline void Engine::EngineImpl::initExtensions(void) {
#ifdef GLEW_OK
	GLenum GlewInitResult;
	glewExperimental = GL_TRUE;
	GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult) {
		FLOG_ERROR("GLEW init failed. Error: %d", GlewInitResult);
		exit(EXIT_FAILURE);
	} else {
		FLOG_DEBUG("OpenGL Version: %s", glGetString(GL_VERSION));
	}
#endif
}

inline void Engine::EngineImpl::initGeometryShading() {
	GLint MaxPatchVertices = 0;
	glGetIntegerv(GL_MAX_PATCH_VERTICES, &MaxPatchVertices);
	FLOG_DEBUG("Max supported patch vertices %d\n", MaxPatchVertices);
	glPatchParameteri(GL_PATCH_VERTICES, 3);
}

#endif

inline void Engine::EngineImpl::initManagement() {
	mTextureManager = puTextureManager(
			new manager::TextureManager(mFileLoader.getRootPath()));

	mShaderManager = puShaderManager(
			new manager::ShaderManager(mFileLoader.getRootPath()));

	mProgramManager = puProgramManager(new manager::ProgramManager());

	mLightManager = puLightManager(
			new manager::LightManager(mWindowWidth, mWindowHeight));

	mSamplerManager = puSamplerManager(new manager::SamplerManager());

	mBufferManager = puBufferManager(new manager::BufferManager());
}

inline void Engine::EngineImpl::initPipelines() {
	/* DR */
	mProgramDRDirecionalLight = mProgramLoader.getDRDirectionalLights(mEngine);
	mProgramDRSpotLight = mProgramLoader.getDRSpotLights(mEngine);
	mProgramDRPointLight = mProgramLoader.getDRPointLights(mEngine);
	mProgramDRDepthless = mProgramLoader.getDRDepthless(mEngine);
	mProgramDRAmbient = mProgramLoader.getDRAmbient(mEngine);

	/* OT */
	mProgramOcclusionBox = mProgramLoader.getOcclusionOptimizedQuery(mEngine);

	/* AO */
	mProgramAOGeometry = mProgramLoader.getAmbientOcclusionGeometry(mEngine);
	mProgramAOColor = mProgramLoader.getAmbientOcclusionColor(mEngine);

	/* T */
	mProgramTextureLookup = mProgramLoader.getQuad(mEngine);
}

inline void Engine::EngineImpl::initUniforms() {
	/* DR */
	glm::vec2 screenSize(mWindowWidth, mWindowHeight);

	mProgramDRDirecionalLight->use();
	mProgramDRDirecionalLight->uniformPush("uWorldPositionAttachment",
	FILLWAVE_POSITION_ATTACHMENT);
	mProgramDRDirecionalLight->uniformPush("uDiffuseTexelAttachment",
	FILLWAVE_DIFFUSE_ATTACHMENT);
	mProgramDRDirecionalLight->uniformPush("uNormalAttachment",
	FILLWAVE_NORMAL_ATTACHMENT);
	mProgramDRDirecionalLight->uniformPush("uSpecularTexelAttachment",
	FILLWAVE_SPECULAR_ATTACHMENT);
	mProgramDRDirecionalLight->uniformPush("uScreenSize", screenSize);
	mProgramDRDirecionalLight->uniformPush("uAOMap", FILLWAVE_AO_UNIT);

	mProgramDRSpotLight->use();
	mProgramDRSpotLight->uniformPush("uWorldPositionAttachment",
	FILLWAVE_POSITION_ATTACHMENT);
	mProgramDRSpotLight->uniformPush("uDiffuseTexelAttachment",
	FILLWAVE_DIFFUSE_ATTACHMENT);
	mProgramDRSpotLight->uniformPush("uNormalAttachment",
	FILLWAVE_NORMAL_ATTACHMENT);
	mProgramDRSpotLight->uniformPush("uSpecularTexelAttachment",
	FILLWAVE_SPECULAR_ATTACHMENT);
	mProgramDRSpotLight->uniformPush("uScreenSize", screenSize);
	mProgramDRSpotLight->uniformPush("uAOMap", FILLWAVE_AO_UNIT);

	mProgramDRPointLight->use();
	mProgramDRPointLight->uniformPush("uWorldPositionAttachment",
	FILLWAVE_POSITION_ATTACHMENT);
	mProgramDRPointLight->uniformPush("uDiffuseTexelAttachment",
	FILLWAVE_DIFFUSE_ATTACHMENT);
	mProgramDRPointLight->uniformPush("uNormalAttachment",
	FILLWAVE_NORMAL_ATTACHMENT);
	mProgramDRPointLight->uniformPush("uSpecularTexelAttachment",
	FILLWAVE_SPECULAR_ATTACHMENT);
	mProgramDRPointLight->uniformPush("uScreenSize", screenSize);
	mProgramDRPointLight->uniformPush("uAOMap", FILLWAVE_AO_UNIT);

	mProgramDRDepthless->use();
	mProgramDRDepthless->uniformPush("uWorldPositionAttachment",
	FILLWAVE_POSITION_ATTACHMENT);
	mProgramDRDepthless->uniformPush("uDiffuseTexelAttachment",
	FILLWAVE_DIFFUSE_ATTACHMENT);
	mProgramDRDepthless->uniformPush("uScreenSize", screenSize);

	mProgramDRAmbient->use();
	mProgramDRAmbient->uniformPush("uDiffuseTexelAttachment",
	FILLWAVE_DIFFUSE_ATTACHMENT);
	mProgramDRAmbient->uniformPush("uScreenSize", screenSize);

	mProgramTextureLookup->use();
	mProgramTextureLookup->uniformPush("uPostProcessingSampler",
	FILLWAVE_DIFFUSE_UNIT);
	core::Program::disusePrograms();
}

inline void Engine::EngineImpl::initOcclusionTest() {
	std::vector<core::VertexPosition> vec = models::BoxOcclusion().getVertices();

	mVAOOcclusion = storeVAO();

	mVBOOcclusion = puVertexBufferPosition(new core::VertexBufferPosition(vec));

	mVBOOcclusion->getAttributes(mProgramOcclusionBox->getHandle());

	mVBOOcclusion->attributesBind(mProgramOcclusionBox);

	mVAOOcclusion->bind();

	mVBOOcclusion->bind();

	mVBOOcclusion->attributesSetForVAO();

	mVBOOcclusion->send();

	mVAOOcclusion->unbind();
}

inline void Engine::EngineImpl::initDeferredShading() {

	models::Material material;

	models::Sphere sphere(3.0f, 10.0f, 10.0f);
	std::vector<core::VertexBasic> vertices = sphere.getVertices();
	std::vector<GLuint> indices = sphere.getIndices();

	mDeferredPointLight = puMesh(
			new models::Mesh(mEngine, material, buildTextureRegion(pTexture()),
					buildTextureRegion(pTexture()), buildTextureRegion(pTexture()),
					mProgramDRPointLight, pProgram(), pProgram(),
					mProgramOcclusionBox, pProgram(), pProgram(),
					mLightManager.get(),
					pVertexBufferBasic(new core::VertexBufferBasic(vertices)),
					pIndexBufferBasic(new core::IndexBufferBasic(indices)),
					nullptr));
}

inline void Engine::EngineImpl::initAmbientOcclusion() {
	mAOGeometryBuffer = mTextureManager->getColor2D(mWindowWidth, mWindowHeight);
	mAOColorBuffer = mTextureManager->getColor2D(mWindowWidth, mWindowHeight);
}

inline void Engine::EngineImpl::initGeometryBuffer() {
	GLint maxAttach = 0, maxDrawBuf = 0;
	glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxAttach);
	glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxDrawBuf);
	if (glm::max(maxAttach, maxDrawBuf) > static_cast<GLint>(mDeferredColorAttachments)) {
//	   mIsDR = GL_TRUE;
		mGBuffer = puFramebufferGeometry(
				new core::FramebufferGeometry(mTextureManager.get(), mWindowWidth,
						mWindowHeight, mDeferredColorAttachments,
						mDeferredDepthAttachments));
	}
}

inline void Engine::EngineImpl::initUniformsCache() {
	mULCCameraPositionSpot = mProgramDRSpotLight->getUniformLocation(
			"uCameraPosition");
	mULCAmbientIntensitySpot = mProgramDRSpotLight->getUniformLocation(
			"uLight.base.ambientIntensity");
	mULCScreenSizeSpot = mProgramDRSpotLight->getUniformLocation("uScreenSize");
	mULCShadowUnitSpot = mProgramDRSpotLight->getUniformLocation("uShadowUnit");
	mULCIsAOSpot = mProgramDRSpotLight->getUniformLocation("uIsAO");

	mULCCameraPositionDirectional =
			mProgramDRDirecionalLight->getUniformLocation("uCameraPosition");
	mULCAmbientIntensityDirectional =
			mProgramDRDirecionalLight->getUniformLocation("uAmbientIntensity");
	mULCScreenSizeDirectional = mProgramDRDirecionalLight->getUniformLocation(
			"uScreenSize");
	mULCShadowUnitDirectional = mProgramDRDirecionalLight->getUniformLocation(
			"uShadowUnit");
	mULCIsAODirectional = mProgramDRDirecionalLight->getUniformLocation("uIsAO");

	mULCCameraPositionPoint = mProgramDRPointLight->getUniformLocation(
			"uCameraPosition");
	mULCMVPPoint = mProgramDRPointLight->getUniformLocation("uMVP");
	mULCScreenSizePoint = mProgramDRPointLight->getUniformLocation(
			"uScreenSize");
	mULCShadowUnitPoint = mProgramDRPointLight->getUniformLocation(
			"uShadowUnit");
	mULCIsAOPoint = mProgramDRSpotLight->getUniformLocation("uIsAO");

	mULCDRDepthlesDiffuseTexel = mProgramDRDepthless->getUniformLocation(
			"uDiffuseTexelAttachment");
	mULCDRDepthlessPositionTexel = mProgramDRDepthless->getUniformLocation(
			"uWorldPositionAttachment");
	mULCDRScreenSize = mProgramDRDepthless->getUniformLocation("uScreenSize");

	uULCDRAScreenSize = mProgramDRAmbient->getUniformLocation("uScreenSize");
	uULCDRADiffuseAttachment = mProgramDRAmbient->getUniformLocation(
			"uDiffuseTexelAttachment");
	uULCDRAAmbientGlobal = mProgramDRAmbient->getUniformLocation("uAmbient");
}

inline void Engine::EngineImpl::initStartup() {

	pProgram program = mProgramLoader.getQuadCustomFragmentShaderStartup(
			mEngine);

	program->use();
	program->uniformPush("uPostProcessingSampler", FILLWAVE_DIFFUSE_UNIT);
	program->uniformPush("uScreenFactor",
			static_cast<GLfloat>(mWindowWidth)
					/ static_cast<GLfloat>(mWindowHeight));
	core::Program::disusePrograms();

	mPostProcessingPassStartup = puPostProcessingPass(
			new common::PostProcessingPass(program,
					mTextureManager->getDynamic("fillwave_quad_startup.frag",
							program, glm::ivec2(mWindowWidth, mWindowHeight)),
					mStartupTimeLimit));

	FLOG_DEBUG("Post processing startup pass added");

	mStartupTexture = mTextureManager->get("logo.png",
	FILLWAVE_TEXTURE_TYPE_NONE, loader::eCompression::none);
	if (not mStartupTexture) {
		mStartupTexture = mTextureManager->get("textures/logo.png",
		FILLWAVE_TEXTURE_TYPE_NONE, loader::eCompression::none);
		if (not mStartupTexture) {
			mStartupTexture = mTextureManager->get("64_64_64.color",
			FILLWAVE_TEXTURE_TYPE_NONE, loader::eCompression::none);
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
	mDebugger = puDebugger(new Debugger(mEngine));
}

void Engine::EngineImpl::reload() {

	initContext();

	mShaderManager->reload();
	mProgramManager->reload();
	mTextureManager->reload();
	mSamplerManager->reload();
	mBufferManager->reload();

	mPickingPixelBuffer->reload();
	reloadPickingBuffer();

	reloadGeometryBuffer();
}

inline void Engine::EngineImpl::reloadGeometryBuffer() {
	mGBuffer->reload();
}

inline void Engine::EngineImpl::reloadPickingBuffer() {
	mPickingRenderableTexture = mTextureManager->getColor2D(mWindowWidth,
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
		evaluateDynamicTextures(time);

		/* Lights evaluation */
		glDepthMask(GL_TRUE);
		evaluateShadowMaps();
		drawScene(time);
		drawText();
		evaluateDebugger();
		mScene->drawCursor();
	}
}

#ifdef __ANDROID__
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
	evaluateDynamicTextures(time);

	/* Lights evaluation */
	if (mScene) {
		evaluateShadowMaps();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		drawScene(time);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		drawText();
		evaluateDebugger();
		mScene->drawCursor();
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
	evaluateDynamicTextures(time);

	/* Lights evaluation */
	if (mScene) {
		evaluateShadowMaps();
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		drawScene(time);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		drawText();
		evaluateDebugger();
		mScene->drawCursor();
	}
}
#endif

inline void Engine::EngineImpl::drawText() {
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
				[](common::PostProcessingPass& pass) -> bool {return pass.isFinished();};
		auto _begin = mPostProcessingPasses.begin();
		auto _end = mPostProcessingPasses.end();

		core::Texture2DRenderableDynamic* textureNext;

		core::Texture2DRenderableDynamic* textureCurrent =
				(*_begin).getFrame().get();

		core::Program* programCurrent;

		drawClear();

		textureCurrent->bindForWriting();

		drawSceneCore();

		for (auto it = _begin; it != _end; it++) {

			auto next = it + 1;

			if (next != _end) {

				textureNext = (*next).getFrame().get();
				textureCurrent = (*it).getFrame().get();
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

				textureCurrent = (*it).getFrame().get();
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
	if (mIsDR) {
		drawSceneCoreDR();
	} else {
		drawSceneCoreFR();
	}
}

inline void Engine::EngineImpl::drawSceneCoreFR() {
	if (mISOQ) {
		drawOcclusionPass();
	}
	drawClear();
	mScene->drawSkybox();
	glClear(GL_DEPTH_BUFFER_BIT);
	mScene->draw();
}

inline void Engine::EngineImpl::drawSceneCoreDR() {
	if (mISOQ) {
		drawOcclusionPass();
	}
	drawClear();
	mGBuffer->setAttachments(); //bind for geom pass
	drawGeometryPass();
	drawAOPass();
	drawColorPass();
	mDebugger->renderGeometryBuffer(mWindowWidth, mWindowHeight,
			mDeferredColorAttachments, mGBuffer.get());
}

inline void Engine::EngineImpl::drawGeometryPass() {
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	mScene->drawDR();
	glDepthMask(GL_FALSE);
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

	mVAOOcclusion->unbind();
}

inline void Engine::EngineImpl::drawAOPass() {
	mAOGeometryBuffer->bindForWriting();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mScene->drawAOG();

	mAOColorBuffer->bindForWriting();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mAOGeometryBuffer->bind(FILLWAVE_POSITION_ATTACHMENT);
	mScene->drawAOC();
}

inline void Engine::EngineImpl::drawColorPassBegin() {
	mGBuffer->setAttachments();

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	mGBuffer->setAttachmentSummaryForWriting();
	mGBuffer->bindAttachments();
}

inline void Engine::EngineImpl::drawColorPass() {
	drawColorPassBegin();

	drawAmbientPass();

	drawDepthlessPass();

	GLint currentTextureUnit = FILLWAVE_SHADOW_FIRST_UNIT;

	mAOColorBuffer->bind(FILLWAVE_AO_UNIT);

	drawLightsSpotPass(currentTextureUnit);
	drawLightsDirectionalPass(currentTextureUnit);
	drawLightsPointPass(currentTextureUnit);

	drawColorPassEnd();
}

inline void Engine::EngineImpl::drawAmbientPass() {
	mProgramDRAmbient->use();
	core::Uniform::push(uULCDRAAmbientGlobal, mScene->getAmbient());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

inline void Engine::EngineImpl::drawDepthlessPass() {
	mProgramDRDepthless->use();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

inline void Engine::EngineImpl::drawLightsSpotPass(GLint& textureUnit) {
	for (GLint i = 0; i < mLightManager->getLightsSpotHowMany(); i++) {

		mProgramDRSpotLight->use();
		mLightManager->updateDeferredBufferSpot(i, mProgramDRSpotLight.get(),
				textureUnit++);

		core::Uniform::push(mULCCameraPositionSpot,
				mScene->getCamera()->getTranslation());
		core::Uniform::push(mULCIsAOSpot, mIsAO ? 1 : 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
}

inline void Engine::EngineImpl::drawLightsDirectionalPass(GLint& textureUnit) {
	for (GLint i = 0; i < mLightManager->getLightsDirectionalHowMany(); i++) {

		mProgramDRDirecionalLight->use();
		mLightManager->updateDeferredBufferDirectional(i,
				mProgramDRDirecionalLight.get(), textureUnit++);

		core::Uniform::push(mULCCameraPositionDirectional,
				mScene->getCamera()->getTranslation());
		core::Uniform::push(mULCIsAODirectional, mIsAO ? 1 : 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
}

inline void Engine::EngineImpl::drawLightsPointPass(GLint& textureUnit) {
	glEnable(GL_STENCIL_TEST);

	for (GLint i = 0; i < mLightManager->getLightsPointHowMany(); i++) {
		// DSStencilPass

		mGBuffer->setAttachmentStencilDepth();

		// Disable color/depth write and enable stencil
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glClear(GL_STENCIL_BUFFER_BIT);
		glDisable(GL_BLEND);

		// We need the stencil test to be enabled but we want it
		// to succeed always. Only the depth test matters.
		glStencilFunc(GL_ALWAYS, 0, 0);

		glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
		glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);

		mProgramDRPointLight->use();
		space::Camera* camera = mScene->getCamera().get();
		mLightManager->updateDeferredBufferPoint(i, mProgramDRPointLight.get(),
				textureUnit++);

		core::Uniform::push(mULCCameraPositionPoint, camera->getTranslation());
		core::Uniform::push(mULCMVPPoint,
				camera->getViewProjection()
						* glm::translate(glm::mat4(1.0),
								mLightManager->getLightPoint(i)->getTranslation()));

		core::Uniform::push(mULCIsAOPoint, mIsAO ? 1 : 0);
//xxx      if runtime changing is not needed
//      if (mIsAO) {
//         core::Uniform::push(mULCIsAOPoint, 1);
//      }

		mDeferredPointLight->drawFast(*(camera));

		//BindForLightPass
		mGBuffer->setAttachmentSummaryForWriting();
		mGBuffer->bindAttachments();

		//draw regular
		glStencilFunc(GL_NOTEQUAL, 0, 0xFF);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);

		mDeferredPointLight->drawFast(*(camera));

		glCullFace(GL_BACK);
		glDisable(GL_BLEND);
	}

	glDisable(GL_STENCIL_TEST);
}

inline void Engine::EngineImpl::drawColorPassEnd() {
	mGBuffer->setAttachmentSummaryForReading();
	glBlitFramebuffer(0, 0, mWindowWidth, mWindowHeight, 0, 0, mWindowWidth,
			mWindowHeight,
			GL_COLOR_BUFFER_BIT,
			GL_LINEAR);
}

inline void Engine::EngineImpl::evaluateStartupAnimation(GLfloat time) {

	drawClear();

	core::Texture2DRenderableDynamic* tex =
			mPostProcessingPassStartup->getFrame().get();

	tex->bindForWriting();

	drawTexture(mStartupTexture.get());

	core::Framebuffer::bindScreenFramebuffer();

	tex->draw(time);

	drawTexture(tex, mPostProcessingPassStartup->getProgram().get());

	mPostProcessingPassStartup->checkTime(time);
}

inline void Engine::EngineImpl::evaluateShadowMaps() {

	glDepthMask(GL_TRUE);

	mLightManager->updateLightEntities();

	GLint currentTextureUnit = FILLWAVE_SHADOW_FIRST_UNIT;

	core::Texture2DRenderable* light2DTexture;
	for (GLint i = 0; i < mLightManager->getLightsSpotHowMany(); i++) {
		space::CameraPerspective camera =
				*(mLightManager->getLightSpot(i)->getShadowCamera().get());
		light2DTexture = mLightManager->getLightSpot(i)->getShadowTexture().get();
		light2DTexture->bindForWriting();
		light2DTexture->bind(currentTextureUnit++);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_DEPTH_BUFFER_BIT);
		mScene->drawDepth(camera);
	}

	for (GLint i = 0; i < mLightManager->getLightsDirectionalHowMany(); i++) {
		space::CameraOrthographic camera =
				*(mLightManager->getLightDirectional(i)->getShadowCamera().get());
		light2DTexture =
				mLightManager->getLightDirectional(i)->getShadowTexture().get();
		light2DTexture->bindForWriting();
		light2DTexture->bind(currentTextureUnit++);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_DEPTH_BUFFER_BIT);
		mScene->drawDepth(camera);
	}

	for (GLint i = 0; i < mLightManager->getLightsPointHowMany(); i++) {
		space::LightPoint* lightPoint = mLightManager->getLightPoint(i).get();
		core::Texture3DRenderable* light3DTexture =
				lightPoint->getShadowTexture().get();
		glm::vec3 lightPosition(lightPoint->getTranslation());
		light3DTexture->bindForWriting();
		light3DTexture->bind(currentTextureUnit);
		for (GLint j = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
				j <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; j++) {
			space::CameraPerspective camera =
					*(lightPoint->getShadowCamera(j).get());
			light3DTexture->setAttachmentFace(j, GL_COLOR_ATTACHMENT0);
			glClearColor(0.0, 0.0, 0.0, 1.0);
			glClear(GL_DEPTH_BUFFER_BIT);
			mScene->drawDepthColor(camera, lightPosition);
		}
		currentTextureUnit++;
	}
	core::Framebuffer::bindScreenFramebuffer();
}

inline void Engine::EngineImpl::evaluateDynamicTextures(
		GLfloat timeExpiredInSeconds) {
	for (auto& it : mTexturesDynamic) {
		it->bindForWriting();
		it->draw(timeExpiredInSeconds);
	}
	core::Framebuffer::bindScreenFramebuffer();
}

inline void Engine::EngineImpl::evaluateTime(GLfloat timeExpiredInSeconds) {
	if (mTimeFactor) {
		actions::TimeEventData data;
		data.mTimePassed = timeExpiredInSeconds;
		actions::TimeEvent timeEvent(data);
		runCallbacks(mTimeCallbacks, &timeEvent);
		mScene->handleHierarchyEvent(&timeEvent);
	}
}

inline void Engine::EngineImpl::evaluateDebugger() {
	GLint mCurentTextureUnit = 0;
	GLint id = 0;
	switch (mDebugger->getState()) {
		case eDebuggerState::lightsSpot:
			mCurentTextureUnit = 0;
			for (GLint i = 0; i < mLightManager->getLightsSpotHowMany(); i++) {
				space::CameraPerspective cameraP =
						*(mLightManager->getLightSpot(i)->getShadowCamera().get());
				mDebugger->renderFromCamera(cameraP, mCurentTextureUnit++); //xxx make more flexible
			}
			for (GLint i = 0; i < mLightManager->getLightsDirectionalHowMany();
					i++) {
				space::CameraOrthographic cameraO =
						*(mLightManager->getLightDirectional(i)->getShadowCamera().get());
				mDebugger->renderFromCamera(cameraO, mCurentTextureUnit++); //xxx make more flexible
			}
			mCurentTextureUnit = 0;
			for (GLint i = 0; i < mLightManager->getLightsSpotHowMany(); i++) {
				mDebugger->renderDepthPerspective(mCurentTextureUnit++);
			}
			for (GLint i = 0; i < mLightManager->getLightsDirectionalHowMany();
					i++) {
				mDebugger->renderDepthOrthographic(mCurentTextureUnit++);
			}
			break;
		case eDebuggerState::lightsSpotDepth:
			mCurentTextureUnit = 0;
			for (GLint i = 0; i < mLightManager->getLightsSpotHowMany(); i++) {
				mDebugger->renderDepthPerspective(mCurentTextureUnit++);
			}
			for (GLint i = 0; i < mLightManager->getLightsDirectionalHowMany();
					i++) {
				mDebugger->renderDepthOrthographic(mCurentTextureUnit++);
			}
			break;
		case eDebuggerState::lightsSpotColor:
			mCurentTextureUnit = 0;
			for (GLint i = 0; i < mLightManager->getLightsSpotHowMany(); i++) {
				space::CameraPerspective cameraP =
						*(mLightManager->getLightSpot(i)->getShadowCamera().get());
				mDebugger->renderFromCamera(cameraP, mCurentTextureUnit++); //xxx make more flexible
			}
			for (GLint i = 0; i < mLightManager->getLightsDirectionalHowMany();
					i++) {
				space::CameraOrthographic cameraO =
						*(mLightManager->getLightDirectional(i)->getShadowCamera().get());
				mDebugger->renderFromCamera(cameraO, mCurentTextureUnit++); //xxx make more flexible
			}
			break;
		case eDebuggerState::lightsPoint:
			break;
		case eDebuggerState::lightsPointDepth: // only light 0
			break;
		case eDebuggerState::lightsPointColor:
			for (GLint j = 0; j < mLightManager->getLightsPointHowMany(); j++) {
				for (int i = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
						i <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; i++) {
					space::CameraPerspective cameraPF =
							*(mLightManager->getLightPoint(j)->getShadowCamera(i).get());
					mDebugger->renderFromCamera(cameraPF, id++);
				}
			}
			break;
		case eDebuggerState::pickingMap:
			mDebugger->renderPickingMap();
			break;
		case eDebuggerState::off:
		default:
			break;
	}
}

void Engine::EngineImpl::runCallbacks(
		std::vector<actions::EngineCallback*>& callbacks,
		actions::EventType* event) {
	for (auto callback : callbacks) {
		callback->perform(mEngine, event);
	}
}

void Engine::EngineImpl::insertResizeScreen(GLuint width, GLuint height) {
	mWindowWidth = width;
	mWindowHeight = height;
	glViewport(0, 0, mWindowWidth, mWindowHeight);

	mTextureManager->resize(mWindowWidth, mWindowHeight);

	mPickingPixelBuffer->setScreenSize(mWindowWidth, mWindowHeight, 4);

	if (mIsDR) {
		mGBuffer->resize(mWindowWidth, mWindowHeight);
	}

	mProgramDRSpotLight->use();
	core::Uniform::push(mULCScreenSizeSpot,
			glm::vec2(mWindowWidth, mWindowHeight));

	mProgramDRDirecionalLight->use();
	core::Uniform::push(mULCScreenSizeDirectional,
			glm::vec2(mWindowWidth, mWindowHeight));

	mProgramDRPointLight->use();
	core::Uniform::push(mULCScreenSizePoint,
			glm::vec2(mWindowWidth, mWindowHeight));

	mProgramDRDepthless->use();
	core::Uniform::push(mULCDRScreenSize,
			glm::vec2(mWindowWidth, mWindowHeight));

	mProgramDRAmbient->use();
	core::Uniform::push(uULCDRAScreenSize,
			glm::vec2(mWindowWidth, mWindowHeight));

	core::Program::disusePrograms();
}

/* Engine callbacks - unregister */

void Engine::EngineImpl::unregisterCallback(
		std::vector<actions::EngineCallback*>& callbacks,
		actions::EngineCallback* callback) {
	auto _compare_function =
			[callback](const actions::EngineCallback* e) -> bool {bool found = (e == callback); if (found) delete callback; return found;};
	auto _begin = callbacks.begin();
	auto _end = callbacks.end();
	auto it = std::remove_if(_begin, _end, _compare_function);
	callbacks.erase(it, _end);
}

inline pShader Engine::EngineImpl::storeShader(
		const std::string& shaderPath,
		const GLuint& shaderType) {
	return mShaderManager->add(shaderPath, shaderType);
}

inline pShader Engine::EngineImpl::storeShader(
		const std::string& shaderName,
		const GLuint& shaderType,
		const std::string& shaderSource) {
	return mShaderManager->add(shaderName, shaderType, shaderSource);
}

pSampler Engine::EngineImpl::storeSO(GLint textureUnit) {
	return mSamplerManager->get(textureUnit);
}

pVertexArray Engine::EngineImpl::storeVAO(models::Reloadable* user) {
	return mBufferManager->getVAO(user);
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

inline void Engine::EngineImpl::clearCallbacks(
		std::vector<actions::EngineCallback*>& callbacks) {
	std::for_each(callbacks.begin(), callbacks.end(),
			[](actions::EngineCallback* e) {delete e;});
	callbacks.clear();
}

} /* fillwave */

#endif /* EXT_FILLWAVE_INC_FILLWAVEIMPL_H_ */
