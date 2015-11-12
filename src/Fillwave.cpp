/*
 * Fillwave.cpp
 *
 *  Created on: Feb 10, 2014
 *      Author: Filip Wasil
 */

/* Plarform specific */
//#include <fillwave/loaders/AndroidLoader.h>
/* Debug */
#include <fillwave/extras/Log.h>

/* Profiling */
#include <fillwave/Profiler.h>

/* Fillwave */

#include <fillwave/Fillwave.h>

/* Assets */
#include <fillwave/Assets.h>

/* Stdlib */
#include <fstream>

/* Implementation */
#include  <impl/FillwaveImpl.h>

namespace fillwave {

#ifdef __ANDROID__

Engine::Engine(std::string rootPath) {
	mImpl = std::unique_ptr<EngineImpl>(new EngineImpl(this, rootPath));
}

Engine::Engine(ANativeActivity* activity) {
	mImpl = std::unique_ptr<EngineImpl>(new EngineImpl(this, activity));
}
#else
Engine::Engine(GLint argc, GLchar* const argv[]) {
	mImpl = std::unique_ptr<EngineImpl>(new EngineImpl(this, argc, argv));
}
#endif

Engine::~Engine() = default;

void Engine::configureBackgroundColor(glm::vec3 color) {
	mImpl->mBackgroundColor = color;
}

void Engine::configureTime(GLfloat timeFactor) {
	mImpl->mTimeFactor = timeFactor;
}

void Engine::draw(GLfloat time) {
	mImpl->draw(time);
}

#ifdef __ANDROID__

#else
void Engine::drawLines(GLfloat time) {
	mImpl->drawLines(time);
}

void Engine::drawPoints(GLfloat time) {
	mImpl->drawPoints(time);
}
#endif

void Engine::drawTexture(core::Texture* t, core::Program* p) {
	mImpl->drawTexture(t, p);
}

void Engine::drawTexture(core::Texture* t) {
	mImpl->drawTexture(t);
}

pLightSpot Engine::storeLightSpot(
		glm::vec3 position,
		glm::quat rotation,
		glm::vec4 color,
		pEntity entity) {
	return mImpl->mLightManager->addLightSpot(
			mImpl->mTextureManager->getShadow2D(mImpl->mWindowWidth,
					mImpl->mWindowHeight), position, rotation, color, entity);
}

pLightPoint Engine::storeLightPoint(
		glm::vec3 position,
		glm::vec4 color,
		pEntity entity) {
	return mImpl->mLightManager->addLightPoint(
			mImpl->mTextureManager->getShadow3D(mImpl->mWindowWidth,
					mImpl->mWindowHeight), position, color, entity);
}

pLightDirectional Engine::storeLightDirectional(
		glm::vec3 position,
		glm::quat rotation,
		glm::vec4 color,
		pEntity entity) {
	return mImpl->mLightManager->addLightDirectional(
			mImpl->mTextureManager->getShadow2D(mImpl->mWindowWidth,
					mImpl->mWindowHeight), position, rotation, color, entity);
}

pShader Engine::storeShaderFragment(const std::string& shaderPath) {
	return mImpl->mShaderManager->add(shaderPath, GL_FRAGMENT_SHADER);
}

pShader Engine::storeShaderFragment(
		const std::string& shaderPath,
		const std::string& shaderSource) {
	return mImpl->mShaderManager->add(shaderPath,
	GL_FRAGMENT_SHADER, shaderSource);
}

pShader Engine::storeShaderVertex(const std::string& shaderPath) {
	return mImpl->mShaderManager->add(shaderPath, GL_VERTEX_SHADER);
}

pShader Engine::storeShaderVertex(
		const std::string& shaderPath,
		const std::string& shaderSource) {
	return mImpl->mShaderManager->add(shaderPath, GL_VERTEX_SHADER, shaderSource);
}

pProgram Engine::storeProgram(
		const std::string& name,
		const std::vector<pShader>& shaders,
		GLboolean skipLinking) {
	return mImpl->mProgramManager->add(name, shaders, skipLinking);
}

pTexture Engine::storeTexture(
		const std::string& texturePath,
		const GLuint& mapType,
		loader::eCompression compression) {
	return mImpl->mTextureManager->get(texturePath, mapType, compression);
}

pTexture2DRenderableDynamic Engine::storeTextureDynamic(
		const std::string& fragmentShaderPath) {
	const std::string path = fragmentShaderPath;
	pProgram program = mImpl->mProgramLoader.getQuadCustomFragmentShader(this,
			fragmentShaderPath);
	pTexture2DRenderableDynamic t = mImpl->mTextureManager->getDynamic(path,
			program, glm::ivec2(mImpl->mWindowWidth, mImpl->mWindowHeight));
	mImpl->mTexturesDynamic.push_back(t);
	return t;
}

pTexture3D Engine::storeTexture3D(
		const std::string& posX,
		const std::string& negX,
		const std::string& posY,
		const std::string& negY,
		const std::string& posZ,
		const std::string& negZ) {
	return mImpl->mTextureManager->get(posX, negX, posY, negY, posZ, negZ);
}

pSampler Engine::storeSO(GLint textureUnit) {
	return mImpl->storeSO(textureUnit);
}

pVertexArray Engine::storeVAO(models::Reloadable* user) {
	return mImpl->storeVAO(user);
}

/* Inputs - insert */

void Engine::insertInputKey(fillwave::actions::KeyboardEvent& event) {
	if (getFocusKey()) {
		getFocusKey()->handlePrivateEvent(&event);
	}
	mImpl->runCallbacks(mImpl->mKeyCallbacks, &event);
}

void Engine::insertInputMouseButton(actions::MouseButtonEvent& event) {
	if (getFocusMouseButton()) {
		getFocusMouseButton()->handlePrivateEvent(&event);
	}
	mImpl->runCallbacks(mImpl->mMouseButtonCallbacks, &event);
}

void Engine::insertInputScroll(actions::ScrollEvent& event) {
	if (getFocusScroll()) {
		getFocusScroll()->handlePrivateEvent(&event);
	}
	mImpl->runCallbacks(mImpl->mScrollCallbacks, &event);
}

void Engine::insertInputCharacter(actions::CharacterEvent& event) {
	if (getFocusChar()) {
		getFocusChar()->handlePrivateEvent(&event);
	}
	mImpl->runCallbacks(mImpl->mCharCallbacks, &event);
}

void Engine::insertInputCharacterMods(actions::CharacterModsEvent& event) {
	if (getFocusCharMods()) {
		getFocusCharMods()->handlePrivateEvent(&event);
	}
	mImpl->runCallbacks(mImpl->mCharModsCallbacks, &event);
}

void Engine::insertInputCursorEnter(actions::CursorEnterEvent& event) {
	if (getFocusCursorEnter()) {
		getFocusCursorEnter()->handlePrivateEvent(&event);
	}
	mImpl->runCallbacks(mImpl->mCursorEnterCallbacks, &event);
}

void Engine::insertInputCursorPosition(actions::CursorPositionEvent& event) {
	if (getFocusCursorPosition()) {
		getFocusCursorPosition()->handlePrivateEvent(&event);
	}
	mImpl->runCallbacks(mImpl->mCursorPositionCallbacks, &event);
}

void Engine::insertInputTouchScreen(actions::TouchEvent& event) {
	if (getFocusTouchScreen()) {
		getFocusTouchScreen()->handlePrivateEvent(&event);
	}
	mImpl->runCallbacks(mImpl->mTouchScreenCallbacks, &event);
}

/* Engine callbacks - clear */

void Engine::clearTimeCallbacks() {
	mImpl->clearCallbacks(mImpl->mTimeCallbacks);
}

void Engine::clearKeyCallbacks() {
	mImpl->clearCallbacks(mImpl->mKeyCallbacks);
}

void Engine::clearMouseButtonCallbacks() {
	mImpl->clearCallbacks(mImpl->mMouseButtonCallbacks);
}

void Engine::clearScrollCallbacks() {
	mImpl->clearCallbacks(mImpl->mScrollCallbacks);
}

void Engine::clearCharCallbacks() {
	mImpl->clearCallbacks(mImpl->mCharCallbacks);
}

void Engine::clearCharModsCallbacks() {
	mImpl->clearCallbacks(mImpl->mCharCallbacks);
}

void Engine::clearCursorEnterCallbacks() {
	mImpl->clearCallbacks(mImpl->mCursorEnterCallbacks);
}

void Engine::clearCursorPositionCallbacks() {
	mImpl->clearCallbacks(mImpl->mCursorPositionCallbacks);
}

void Engine::clearTouchScreenCallbacks() {
	mImpl->clearCallbacks(mImpl->mTouchScreenCallbacks);
}

/* Engine callbacks - register */

void Engine::registerTimeCallback(actions::EngineCallback* callback) {
	mImpl->mTimeCallbacks.push_back(callback);
}

void Engine::registerKeyCallback(actions::EngineCallback* callback) {
	mImpl->mKeyCallbacks.push_back(callback);
}

void Engine::registerMouseButtonCallback(actions::EngineCallback* callback) {
	mImpl->mMouseButtonCallbacks.push_back(callback);
}

void Engine::registerScrollCallback(actions::EngineCallback* callback) {
	mImpl->mScrollCallbacks.push_back(callback);
}

void Engine::registerCharCallback(actions::EngineCallback* callback) {
	mImpl->mCharCallbacks.push_back(callback);
}

void Engine::registerCharModsCallback(actions::EngineCallback* callback) {
	mImpl->mCharModsCallbacks.push_back(callback);
}

void Engine::registerCursorEnterCallback(actions::EngineCallback* callback) {
	mImpl->mCursorEnterCallbacks.push_back(callback);
}

void Engine::registerCursorPositionCallback(actions::EngineCallback* callback) {
	mImpl->mCursorPositionCallbacks.push_back(callback);
}

void Engine::registerTouchScreenCallback(actions::EngineCallback* callback) {
	mImpl->mTouchScreenCallbacks.push_back(callback);
}

/* Engine callbacks - unregister */
void Engine::unregisterTimeCallback(actions::EngineCallback* callback) {
	mImpl->unregisterCallback(mImpl->mTimeCallbacks, callback);
}

void Engine::unregisterKeyCallback(actions::EngineCallback* callback) {
	mImpl->unregisterCallback(mImpl->mKeyCallbacks, callback);
}

void Engine::unregisterMouseButtonCallback(actions::EngineCallback* callback) {
	mImpl->unregisterCallback(mImpl->mMouseButtonCallbacks, callback);
}

void Engine::unregisterScrollCallback(actions::EngineCallback* callback) {
	mImpl->unregisterCallback(mImpl->mScrollCallbacks, callback);
}

void Engine::unregisterCharCallback(actions::EngineCallback* callback) {
	mImpl->unregisterCallback(mImpl->mCharCallbacks, callback);
}

void Engine::unregisterCharModsCallback(actions::EngineCallback* callback) {
	mImpl->unregisterCallback(mImpl->mCharModsCallbacks, callback);
}

void Engine::unregisterCursorEnterCallback(actions::EngineCallback* callback) {
	mImpl->unregisterCallback(mImpl->mCursorEnterCallbacks, callback);
}

void Engine::unregisterCursorPositionCallback(
		actions::EngineCallback* callback) {
	mImpl->unregisterCallback(mImpl->mCursorPositionCallbacks, callback);
}

void Engine::unregisterTouchScreenCallback(actions::EngineCallback* callback) {
	mImpl->unregisterCallback(mImpl->mTouchScreenCallbacks, callback);
}

/* Inputs - setFocus */
void Engine::setFocusKey(pEntity entity) {
	mImpl->mFocusKey = entity;
}

void Engine::setFocusMouseButton(pEntity entity) {
	mImpl->mFocusMouseButton = entity;
}

void Engine::setFocusScroll(pEntity entity) {
	mImpl->mFocusScroll = entity;
}

void Engine::setFocusChar(pEntity entity) {
	mImpl->mFocusChar = entity;
}

void Engine::setFocusCharMods(pEntity entity) {
	mImpl->mFocusCharMods = entity;
}

void Engine::setFocusCursorEnter(pEntity entity) {
	mImpl->mFocusCursorEnter = entity;
}

void Engine::setFocusCursorPosition(pEntity entity) {
	mImpl->mFocusCursorPosition = entity;
}

/* Inputs - getFocus */
pEntity Engine::getFocusKey() const {
	return mImpl->mFocusKey;
}

pEntity Engine::getFocusMouseButton() const {
	return mImpl->mFocusMouseButton;
}

pEntity Engine::getFocusScroll() const {
	return mImpl->mFocusScroll;
}

pEntity Engine::getFocusChar() const {
	return mImpl->mFocusChar;
}

pEntity Engine::getFocusCharMods() const {
	return mImpl->mFocusCharMods;
}

pEntity Engine::getFocusCursorEnter() const {
	return mImpl->mFocusCursorEnter;
}

pEntity Engine::getFocusCursorPosition() const {
	return mImpl->mFocusCursorPosition;
}

pEntity Engine::getFocusTouchScreen() const {
	return mImpl->mFocusTouchScreen;
}

pText Engine::storeText(
		std::string content,
		std::string fontName,
		GLfloat startingPositionX,
		GLfloat startingPositionY,
		GLfloat scale,
		glm::vec4 color,
		eTextEffect effect) {
	/* Check for the font texture */
	if (not mImpl->mTextureManager->check(fontName + ".png")) {
		mImpl->mFontLoader.load(mImpl->mFileLoader.getRootPath() + fontName);
	}

	pTexture t = mImpl->mTextureManager->get(fontName + ".png",
	FILLWAVE_TEXTURE_TYPE_NONE, eCompression::none, eFlip::vertical);

	Font* font = nullptr;
	for (auto& it : mImpl->mFontManager) {
		if (it->mName == fontName) {
			font = it.get();
		}
	}

	if (not font) {
		std::ifstream myfile(mImpl->mFileLoader.getRootPath(fontName + ".meta"));
		if (!myfile.is_open()) {
			FLOG_ERROR("No text added. Could not write to metadata file: %s",
					(fontName + ".meta").c_str());
			return pText();
		}
		std::string line;
		std::string ASCII, xMin, width, yMin, height, yOffset;
		GLfloat fXMin, fWidth, fYMin, fHeight, fYOffset;
		GLint iASCII;
		Font* newFont = new Font();
		GLint control = 0;
		while (!myfile.eof()) {
			getline(myfile, line);
			myfile >> iASCII >> fXMin >> fWidth >> fYMin >> fHeight >> fYOffset;
			newFont->mWidths[iASCII] = fWidth;
			newFont->mOffsets[iASCII] = 1.0f - fHeight - fYOffset;
			if (control++ > 512) { //xxx limit
				FLOG_ERROR("Metadata can not be read for file %s.",
						(fontName + ".meta").c_str());
				myfile.close();
				delete newFont;
				return pText();
			}
		}
		myfile.close();
		mImpl->mFontManager.push_back(pFont(newFont));
		font = newFont;
	}

	pText text = pText(
			new models::Text(content, t, startingPositionX, startingPositionY,
					this, scale, font, color, effect));
	mImpl->mTextManager.push_back(pText(text));
	return text;
}

void Engine::clearText(pText text) {
	auto _compare_function = [text](pText t) -> bool {return (t == text);};
	auto _begin = mImpl->mTextManager.begin();
	auto _end = mImpl->mTextManager.end();
	auto it = std::remove_if(_begin, _end, _compare_function);
	mImpl->mTextManager.erase(it, _end);
}

void Engine::clearLight(pLightSpot light) {
	mImpl->mLightManager->removeLight(light);
}

void Engine::clearLight(pLightDirectional light) {
	mImpl->mLightManager->removeLight(light);
}

void Engine::clearLight(pLightPoint light) {
	mImpl->mLightManager->removeLight(light);
}

void Engine::clearLights() {
	mImpl->mLightManager->removeLights();
}

glm::ivec2 Engine::getScreenSize() const {
	return glm::ivec2(mImpl->mWindowWidth, mImpl->mWindowHeight);
}

void Engine::insertResizeScreen(GLuint width, GLuint height) {
	mImpl->insertResizeScreen(width, height);

	for (auto& it : mImpl->mTextManager) { //xxx todo optimize to update only VBO
		it->editAspectRatio(this);
	}
}

GLuint Engine::getFramesPassed() {
	GLuint result = mImpl->mFrameCounter;
	mImpl->mFrameCounter = 0;
	return result;
}

GLfloat Engine::getStartupAnimationTime() const {
	return mImpl->mStartupTimeLimit;
}

void Engine::setCurrentScene(pScene scene) {
	if (scene) {
		if (mImpl->mScene) {
			mImpl->mScene->onHide();
		}
		mImpl->mScene = scene;
		mImpl->mScene->onShow();
	}
}

pScene Engine::getCurrentScene() const {
	return mImpl->mScene;
}

manager::LightManager* Engine::getLightManager() const {
	return mImpl->mLightManager.get();
}

puPhysicsMeshBuffer Engine::getPhysicalMeshBuffer(
		const std::string& shapePath) {
	PhysicsMeshBuffer* buffer = new PhysicsMeshBuffer();
	const fScene* scene = mImpl->mImporter.ReadFile(
			(mImpl->mFileLoader.getRootPath() + shapePath).c_str(),
			FILLWAVE_PROCESS_TRIANGULATE |
			FILLWAVE_PROCESS_SORT_BY_P_TYPE |
			FILLWAVE_PROCESS_CALC_TANGENT_SPACE);
	if (scene) {
		for (GLuint i = 0; i < scene->mNumMeshes; i++) {
			const fMesh* shape = scene->mMeshes[i];
			buffer->mNumFaces = shape->mNumFaces;
			buffer->mVertices.reserve(shape->mNumVertices);
			buffer->mIndices.reserve(shape->mNumFaces * 3);
			for (GLuint j = 0; j < shape->mNumFaces; j++) {
				buffer->mIndices.push_back(shape->mFaces[j].mIndices[0]);
				buffer->mIndices.push_back(shape->mFaces[j].mIndices[1]);
				buffer->mIndices.push_back(shape->mFaces[j].mIndices[2]);
			}
			for (GLuint z = 0; z < shape->mNumVertices; z++) {
				glm::vec3 vertex(shape->mVertices[z].x, shape->mVertices[z].y,
						shape->mVertices[z].z);
				buffer->mVertices.push_back(vertex);
			}
			break;      //for now fillwave supports only one mesh here;
		}
	}
	return puPhysicsMeshBuffer(buffer);
}

void Engine::addPostProcess(
		const std::string& fragmentShaderPath,
		GLfloat lifeTime) {
	pProgram program = mImpl->mProgramLoader.getQuadCustomFragmentShader(this,
			fragmentShaderPath);
	common::PostProcessingPass pass(program,
			mImpl->mTextureManager->getDynamic(fragmentShaderPath, program,
					glm::ivec2(mImpl->mWindowWidth, mImpl->mWindowHeight)),
			lifeTime);
	mImpl->mPostProcessingPasses.push_back(pass);
	FLOG_DEBUG("Post processing pass added: %s", fragmentShaderPath.c_str());
}

void Engine::configureFPSCounter(
		std::string fontName,
		GLfloat xPosition,
		GLfloat yPosition,
		GLfloat size) {
	if (fontName.size() > 1) {
		mImpl->mFPSText = storeText("", fontName, xPosition, yPosition, size);

		/* Provide callback to refresh the FPS value */
		mImpl->mTextFPSCallback = new actions::FPSCallback(mImpl->mFPSText);
		registerTimeCallback(mImpl->mTextFPSCallback);
	} else {
		mImpl->mFPSText.reset();
		unregisterTimeCallback(mImpl->mTextFPSCallback);
	}
}

void Engine::configureFileLogging(std::string fileName) {
	if (fileName.size() > 1) {
		FLOG_INFO("File %s will be cleaned and used for logging.",
				fileName.c_str());
		setLogPath(fileName);
	} else {
		setFileInvalid();
		FLOG_INFO("File logging disabled.");
	}
}

void Engine::reload() {
	mImpl->reload();
}

void Engine::log() {
	FLOG_INFO("Fillwave engine");
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	FLOG_INFO("Renderer: %s\n", renderer);
	FLOG_INFO("OpenGL version supported %s\n", version);
}

void Engine::pick(GLuint x, GLuint y) {
	mImpl->mPickingRenderableTexture->bindForRendering();

	mImpl->drawClear();

	mImpl->mScene->drawPicking();

	mImpl->mPickingPixelBuffer->bind();

	glReadPixels(0, 0, mImpl->mWindowWidth, mImpl->mWindowHeight, GL_RGBA,
	GL_UNSIGNED_BYTE, 0);

	FLOG_CHECK("glReadPixels failed");
#ifdef __ANDROID__
	GLubyte* data = (GLubyte*)mImpl->mPickingPixelBuffer->mapRange(GL_MAP_READ_BIT);
#else
	GLubyte* data = (GLubyte*) mImpl->mPickingPixelBuffer->map(GL_READ_WRITE);
#endif

	glm::ivec4 colorRead = mImpl->pickingBufferGetColor(data, x, y);
	mImpl->mPickingPixelBuffer->unmap();
	mImpl->mPickingPixelBuffer->unbind();
	core::Framebuffer::bindScreenFramebuffer();
	mImpl->mScene->draw();
	mImpl->mScene->pick(colorRead);
}

void Engine::captureFramebufferToFile(const std::string& name) {
	mImpl->mPickingRenderableTexture->bindForRendering();
	mImpl->drawClear();
	mImpl->mScene->draw();
	mImpl->mPickingPixelBuffer->bind();
	glReadPixels(0, 0, mImpl->mWindowWidth, mImpl->mWindowHeight, GL_RGBA,
	GL_UNSIGNED_BYTE, 0);
	FLOG_CHECK("reading pixel buffer failed");
#ifdef __ANDROID__
	GLubyte* data = (GLubyte*)mImpl->mPickingPixelBuffer->mapRange(GL_MAP_READ_BIT);
#else
	GLubyte* data = (GLubyte*) mImpl->mPickingPixelBuffer->map(GL_READ_WRITE);
#endif
	data[mImpl->mWindowWidth * mImpl->mWindowHeight * 4] = '\0';
	FILE* file;
	file = fopen(mImpl->mFileLoader.getRootPath(name).c_str(), "w");
	if (file == nullptr) {
		FLOG_ERROR("Error when takin' screenshot");
		exit(1);
	}
	for (GLuint i = 0; i < mImpl->mWindowWidth * mImpl->mWindowHeight; i++) {
		fprintf(file, "%c", data[4 * i]);
		fprintf(file, "%c", data[4 * i + 1]);
		fprintf(file, "%c", data[4 * i + 2]);
		fprintf(file, "%c", data[4 * i] + 3);
	}
	fclose(file);
	mImpl->mPickingPixelBuffer->unmap();
	mImpl->mPickingPixelBuffer->unbind();
	core::Framebuffer::bindScreenFramebuffer();
	mImpl->mScene->draw();
}

void Engine::captureFramebufferToBuffer(
		GLubyte* buffer,
		GLint* sizeInBytes,
		GLuint format,
		GLint bytesPerPixel) {
	mImpl->mPickingRenderableTexture->bindForRendering();
	mImpl->drawClear();
	mImpl->mScene->draw();
	mImpl->mPickingPixelBuffer->bind();
	glReadPixels(0, 0, mImpl->mWindowWidth, mImpl->mWindowHeight, format,
	GL_UNSIGNED_BYTE, 0);
	FLOG_CHECK("reading pixel buffer failed");
#ifdef __ANDROID__
	buffer = (GLubyte*)mImpl->mPickingPixelBuffer->mapRange(GL_MAP_READ_BIT);
#else
	buffer = (GLubyte*) mImpl->mPickingPixelBuffer->map(GL_READ_WRITE);
#endif
	*sizeInBytes = mImpl->mWindowWidth * mImpl->mWindowHeight * bytesPerPixel;
	buffer[*sizeInBytes] = '\0';
}

const fScene* Engine::getModelFromFile(std::string path) {
	FLOG_DEBUG("Reading model %s", path.c_str());
#ifdef FILLWAVE_COMPILATION_TINY_ASSET_LOADER
	return nullptr;
#else
	return mImpl->mImporter.ReadFile(
			(mImpl->mFileLoader.getRootPath() + path).c_str(),
			aiProcess_Triangulate | aiProcess_SortByPType
					| aiProcess_CalcTangentSpace);
#endif
}

GLboolean Engine::isDR() const {
	return mImpl->mIsDR;
}

#ifndef __ANDROID__

pShader Engine::storeShaderGeometry(const std::string& shaderPath) {
	return mImpl->mShaderManager->add(shaderPath, GL_GEOMETRY_SHADER);
}

pShader Engine::storeShaderGeometry(
		const std::string& shaderPath,
		const std::string& shaderSource) {
	return mImpl->mShaderManager->add(shaderPath,
	GL_GEOMETRY_SHADER, shaderSource);
}

pShader Engine::storeShaderTesselationControl(const std::string& shaderPath) {
	return mImpl->mShaderManager->add(shaderPath, GL_TESS_CONTROL_SHADER);
}

pShader Engine::storeShaderTesselationControl(
		const std::string& shaderPath,
		const std::string& shaderSource) {
	return mImpl->mShaderManager->add(shaderPath,
	GL_TESS_CONTROL_SHADER, shaderSource);
}

pShader Engine::storeShaderTesselationEvaluation(
		const std::string& shaderPath) {
	return mImpl->mShaderManager->add(shaderPath, GL_TESS_EVALUATION_SHADER);
}

pShader Engine::storeShaderTesselationEvaluation(
		const std::string& shaderPath,
		const std::string& shaderSource) {
	return mImpl->mShaderManager->add(shaderPath,
	GL_TESS_EVALUATION_SHADER, shaderSource);
}

#endif

void Engine::configureDebugger(eDebuggerState state) {
	mImpl->mDebugger->setState(state);
}

}
/* fillwave */
