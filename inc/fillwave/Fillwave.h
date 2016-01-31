/*
 * Fillwave.h
 *
 *  Created on: Feb 10, 2014
 *      Author: Filip Wasil
 */

#ifndef FILLWAVE_H_
#define FILLWAVE_H_

#include <fillwave/space/base/IScene.h>

#include <fillwave/space/LightPoint.h>
#include <fillwave/space/LightSpot.h>
#include <fillwave/space/LightDirectional.h>
#include <fillwave/hud/Text.h>

/* Debugger */
#include <fillwave/Debugger.h>

/* Loaders */
#include <fillwave/loaders/ProgramLoader.h>

/* Common */
#include <fillwave/common/PhysicsMeshBuffer.h>

#ifdef __ANDROID__
struct ANativeActivity;
#endif

namespace fillwave {

/*! \class Engine
 * \brief Fillwave engine.
 */

class Engine {
public:
#ifdef __ANDROID__
	Engine(std::string rootPath);
	Engine(ANativeActivity* activity);
#else
	Engine(GLint argc, GLchar* const argv[]);
#endif
	virtual ~Engine();

	/* Configuration */
	void configureDebugger(eDebuggerState state);
	void configureFileLogging(std::string fileName = "");
	void configureFPSCounter(
			std::string fontName = "",
			glm::vec2 position = glm::vec2(-0.95, 0.95),
			GLfloat size = 100.0);
	void configureBackgroundColor(glm::vec3 color);
	void configureTime(GLfloat timeFactor);

	/* Draw */
	void draw(GLfloat time);
	void drawLines(GLfloat time);
	void drawPoints(GLfloat time);
	void drawTexture(core::Texture* t, core::Program* p);
	void drawTexture(core::Texture* t);

	/* Assets */
	puPhysicsMeshBuffer getPhysicalMeshBuffer(const std::string& shapePath);
	const fScene* getModelFromFile(std::string path); /* xxx remove */

	/* Scene */
	void setCurrentScene(pIScene scene);
	pIScene getCurrentScene() const;

	/* Time */
	GLuint getFramesPassed();
	GLfloat getStartupAnimationTime() const;

	/* Store shaders */
	pShader storeShaderFragment(const std::string& shaderPath);
	pShader storeShaderVertex(const std::string& shaderPath);

	pShader storeShaderFragment(
			const std::string& shaderPath,
			const std::string& shaderSource);
	pShader storeShaderVertex(
			const std::string& shaderPath,
			const std::string& shaderSource);

#ifdef FILLWAVE_GLES_3_0
#else
	pShader storeShaderGeometry(const std::string& shaderPath);
	pShader storeShaderTesselationControl(const std::string& shaderPath);
	pShader storeShaderTesselationEvaluation(const std::string& shaderPath);

	pShader storeShaderGeometry(
			const std::string& shaderPath,
			const std::string& shaderSource);
	pShader storeShaderTesselationControl(
			const std::string& shaderPath,
			const std::string& shaderSource);
	pShader storeShaderTesselationEvaluation(
			const std::string& shaderPath,
			const std::string& shaderSource);
#endif

	pProgram storeProgram(
			const std::string& name,
			const std::vector<pShader>& shaders,
			GLboolean skipLinking = GL_FALSE);

	/* Store textures */
	pTexture2D storeTexture(const std::string& texturePath, const GLuint& mapType =
	FILLWAVE_TEXTURE_TYPE_NONE, framework::eCompression compression =
			framework::eCompression::eNone);

	pTexture2DRenderable storeTextureRenderable();

	pTexture2DRenderableDynamic storeTextureDynamic(
			const std::string& fragmentShaderPath);

	pTexture3D storeTexture3D(
			const std::string& posX,
			const std::string& negX,
			const std::string& posY,
			const std::string& negY,
			const std::string& posZ,
			const std::string& negZ);

	/* Store lights */
	pLightSpot storeLightSpot(
			glm::vec3 position,
			glm::quat rotation,
			glm::vec4 color,
			pMoveable followed = pEntity());

	pLightPoint storeLightPoint(
			glm::vec3 position,
			glm::vec4 color,
			pMoveable followed = pEntity());

	pLightDirectional storeLightDirectional(
			glm::vec3 position,
			glm::quat rotation,
			glm::vec4 color,
			pMoveable followed = pEntity());

	/* Store text */
	pText storeText(
			std::string content,
			std::string fontName,
			glm::vec2 position,
			GLfloat scale = 1.0,
			glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0),
			eTextEffect effect = eTextEffect::eNone);

	/* Store sampler */
	pSampler storeSO(GLint textureUnit);

	/* Store vertex array objects */
	pVertexArray storeVAO(framework::IReloadable* user = nullptr);

	/* Clear */
	void clearText(pText text);
	void clearLight(pLightSpot light);
	void clearLight(pLightDirectional);
	void clearLight(pLightPoint light);
	void clearLights();

	/* Pick */
	void pick(GLuint x, GLuint y);

	/* Screen */
	glm::ivec2 getScreenSize() const;
	GLfloat getScreenAspectRatio() const;

	/* Log */
	void log();

	/* Screenshot */
	void captureFramebufferToFile(const std::string& name);
	void captureFramebufferToBuffer(
			GLubyte* buffer,
			GLint* sizeInBytes,
			GLuint format = GL_RGBA,
			GLint bytesPerPixel = 4);

	/* Post processing */
	void addPostProcess(const std::string& fragmentShaderPath, GLfloat lifeTime =
	FILLWAVE_ENDLESS);

	/* Inputs - focus */
	void setFocus(eEventType eventType, pEntity entity);
	pEntity getFocus(eEventType eventType) const;
	void clearFocus(eEventType eventType);

	/* Inputs */
	void insertInput(framework::EventType& event);
	void insertResizeScreen(GLuint width, GLuint height);
	void registerCallback(framework::Callback* callback);
	void unregisterCallback(framework::Callback* callback);
	void clearCallback(framework::Callback* callback);
	void clearCallbacks(eEventType eventType);
	void clearCallbacks();

	void reload();

	framework::LightSystem* getLightSystem() const;
	framework::TextureManager* getTextureManager() const;

private:
	struct EngineImpl;
	std::unique_ptr<EngineImpl> mImpl;
};
} /* fillwave */

#endif /*  FILLWAVE_H_ */

/* Header for class com_example_runningremote_RunningRemote */
