/*
 * Fillwave.cpp
 *
 *  Created on: Feb 10, 2014
 *      Author: Filip Wasil
 */

/* Debug */
#include <fillwave/Log.h>

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
	mImpl = make_unique<EngineImpl>(this, rootPath);
	/* This init has to be outside of the initializer list,
	 * because it needs mImpl to be created fully before Initialization.
	 * mImpl uses Engine functions */
	mImpl->init();
}

Engine::Engine(ANativeActivity* activity) {
	mImpl = make_unique<EngineImpl>(this, activity);
	/* This init has to be outside of the initializer list,
	 * because it needs mImpl to be created fully before Initialization.
	 * mImpl uses Engine functions */
	mImpl->init();
}
#else
Engine::Engine(GLint argc, GLchar* const argv[]) {
	mImpl = make_unique<EngineImpl>(this, argc, argv);
	/* This init has to be outside of the initializer list,
	 * because it needs mImpl to be created fully before Initialization.
	 * mImpl uses Engine functions */
	mImpl->init();
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

#ifdef FILLWAVE_GLES_3_0
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
		pMoveable followed) {
	return mImpl->mLights->mLightsSpot.add(
		mImpl->mTextures->getShadow2D(mImpl->mWindowWidth, mImpl->mWindowHeight),
		position, rotation, color, followed);
}

pLightPoint Engine::storeLightPoint(
		glm::vec3 position,
		glm::vec4 color,
		pMoveable followed) {
	return mImpl->mLights->mLightsPoint.add(
		mImpl->mTextures->getShadow3D(mImpl->mWindowWidth, mImpl->mWindowHeight),
		position, color, followed);
}

pLightDirectional Engine::storeLightDirectional(
		glm::vec3 position,
		glm::quat rotation,
		glm::vec4 color,
		pMoveable followed) {
	return mImpl->mLights->mLightsDirectional.add(
		mImpl->mTextures->getShadow2D(mImpl->mWindowWidth, mImpl->mWindowHeight),
		position, rotation, color, followed);
}

pProgram Engine::storeProgram(
		const std::string& name,
		const std::vector<pShader>& shaders,
		GLboolean skipLinking) {
	return mImpl->mPrograms.add(name, shaders, skipLinking);
}

core::Texture2D* Engine::storeTexture(
		const std::string& texturePath,
		framework::eCompression compression) {
	return mImpl->mTextures->get(texturePath, compression);
}

pTexture2DRenderable Engine::storeTextureRenderable() {
	return mImpl->mTextures->getColor2D(mImpl->mWindowWidth,
		mImpl->mWindowHeight);
}

pTexture2DRenderableDynamic Engine::storeTextureDynamic(
		const std::string& fragmentShaderPath) {
	const std::string path = fragmentShaderPath;
	pProgram program = mImpl->mProgramLoader.getQuadCustomFragmentShader(
		fragmentShaderPath);
	pTexture2DRenderableDynamic t = mImpl->mTextures->getDynamic(path, program,
		glm::ivec2(mImpl->mWindowWidth, mImpl->mWindowHeight));
	return t;
}

pTexture3D Engine::storeTexture3D(
		const std::string& posX,
		const std::string& negX,
		const std::string& posY,
		const std::string& negY,
		const std::string& posZ,
		const std::string& negZ) {
	return mImpl->mTextures->get(posX, negX, posY, negY, posZ, negZ);
}

pSampler Engine::storeSO(GLint textureUnit) {
	return mImpl->mSamplers.add(textureUnit, textureUnit);
}

pVertexArray Engine::storeVAO(framework::IReloadable* user) {
	return mImpl->mBuffers.getVAO(user);
}

/* Inputs - insert */
void Engine::insertInput(framework::EventType& event) {
	if (pEntity moveable = getFocus(event.getType())) {
		moveable->handlePrivateEvent(event);
	}
	mImpl->runCallbacks(event);
}

/* Engine callbacks - clear */
void Engine::clearCallback(framework::Callback* callback) {
	mImpl->clearCallback(callback);
}

void Engine::clearCallbacks(eEventType eventType) {
	mImpl->clearCallbacks(eventType);
}

void Engine::clearCallbacks() {
	mImpl->clearCallbacks();
}

/* Callbacks registeration */
void Engine::registerCallback(framework::Callback* callback) {
	mImpl->registerCallback(callback);
}

void Engine::unregisterCallback(framework::Callback* callback) {
	mImpl->unregisterCallback(callback);
}

/* Focus set */
void Engine::setFocus(eEventType eventType, pEntity entity) {
	mImpl->mFocus[eventType] = entity;
}

pEntity Engine::getFocus(eEventType eventType) const {
	return mImpl->mFocus[eventType];
}

void Engine::clearFocus(eEventType eventType) {
	mImpl->mFocus[eventType] = pEntity();
}

pText Engine::storeText(
		std::string content,
		std::string fontName,
		glm::vec2 position,
		GLfloat scale,
		glm::vec4 color,
		eTextEffect effect) {
	/* Check for the font texture */
	if (not mImpl->mTextures->get(fontName + ".png")) {
		mImpl->mFontLoader.load(mImpl->mFileLoader.getRootPath() + fontName);
	}
	core::Texture2D* t = mImpl->mTextures->get(fontName + ".png",
		framework::eCompression::eNone, framework::eFlip::eVertical);

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

	pText text = std::make_shared < framework::Text
			> (content, t, position, this, scale, font, color, effect);
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
	mImpl->mLights->mLightsSpot.remove(light);
}

void Engine::clearLight(pLightDirectional light) {
	mImpl->mLights->mLightsDirectional.remove(light);
}

void Engine::clearLight(pLightPoint light) {
	mImpl->mLights->mLightsPoint.remove(light);
}

void Engine::clearLights() {
	mImpl->mLights->clear();
}

glm::ivec2 Engine::getScreenSize() const {
	return glm::ivec2(mImpl->mWindowWidth, mImpl->mWindowHeight);
}

GLfloat Engine::getScreenAspectRatio() const {
	return mImpl->mWindowAspectRatio;
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

void Engine::setCurrentScene(pIScene scene) {
	if (scene) {
		if (mImpl->mScene) {
			mImpl->mScene->onHide();
		}
		mImpl->mScene = scene;
		mImpl->mScene->onShow();
		mImpl->mScene->resetRenderer(getScreenSize().x, getScreenSize().y);
	}
}

pIScene Engine::getCurrentScene() const {
	return mImpl->mScene;
}

framework::LightSystem* Engine::getLightSystem() const {
	return mImpl->mLights.get();
}

framework::TextureSystem* Engine::getTextureSystem() const {
	return mImpl->mTextures.get();
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
	pProgram program = mImpl->mProgramLoader.getQuadCustomFragmentShader(
		fragmentShaderPath);
	core::PostProcessingPass pass(program,
		mImpl->mTextures->getDynamic(fragmentShaderPath, program,
			glm::ivec2(mImpl->mWindowWidth, mImpl->mWindowHeight)), lifeTime);
	mImpl->mPostProcessingPasses.push_back(pass);
	FLOG_DEBUG("Post processing pass added: %s", fragmentShaderPath.c_str());
}

void Engine::configureFPSCounter(
		std::string fontName,
		glm::vec2 position,
		GLfloat size) {
	if (fontName.size() > 1) {
		mImpl->mFPSText = storeText("", fontName, position, size);

		/* Provide callback to refresh the FPS value */
		mImpl->mTextFPSCallback = new framework::FPSCallback(this,
			mImpl->mFPSText);
		registerCallback(mImpl->mTextFPSCallback);
	} else {
		mImpl->mFPSText.reset();
		unregisterCallback(mImpl->mTextFPSCallback);
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
#ifdef FILLWAVE_GLES_3_0
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
#ifdef FILLWAVE_GLES_3_0
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
#ifdef FILLWAVE_GLES_3_0
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

template <GLuint T>
pShader Engine::storeShader(const std::string& shaderPath) {
	std::string shaderSource = "";
	const std::string fullPath = mImpl->mFileLoader.getRootPath() + shaderPath;
	ReadFile(fullPath, shaderSource);
	return mImpl->mShaders.add(fullPath, T, shaderSource);
}

template <GLuint T>
pShader Engine::storeShader(
		const std::string& shaderPath,
		const std::string& shaderSource) {
	const std::string fullPath = mImpl->mFileLoader.getRootPath() + shaderPath;
	return mImpl->mShaders.add(fullPath, T, shaderSource);
}

template pShader Engine::storeShader<GL_VERTEX_SHADER>(const std::string&);
template pShader Engine::storeShader<GL_FRAGMENT_SHADER>(const std::string&);
template pShader Engine::storeShader<GL_VERTEX_SHADER>(const std::string&, const std::string&);
template pShader Engine::storeShader<GL_FRAGMENT_SHADER>(const std::string&, const std::string&);
#ifdef FILLWAVE_GLES_3_0
#else
template pShader Engine::storeShader<GL_TESS_CONTROL_SHADER>(const std::string&);
template pShader Engine::storeShader<GL_TESS_EVALUATION_SHADER>(const std::string&);
template pShader Engine::storeShader<GL_GEOMETRY_SHADER>(const std::string&);
template pShader Engine::storeShader<GL_TESS_CONTROL_SHADER>(const std::string&, const std::string&);
template pShader Engine::storeShader<GL_TESS_EVALUATION_SHADER>(const std::string&, const std::string&);
template pShader Engine::storeShader<GL_GEOMETRY_SHADER>(const std::string&, const std::string&);
#endif

void Engine::configureDebugger(eDebuggerState state) {
	mImpl->mDebugger->setState(state);
}

}
/* fillwave */
