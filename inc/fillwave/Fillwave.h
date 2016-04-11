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

/* Common */
#include <fillwave/common/PhysicsMeshBuffer.h>

#ifdef __ANDROID__
struct ANativeActivity;
#endif

namespace fillwave {

/*! \class Engine
 * \brief Fillwave engine.
 */

class Engine final {
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

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
	const aiScene* getModelFromFile(std::string path); /* xxx remove */
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

	/* Scene */
	void setCurrentScene(pIScene scene);
	pIScene getCurrentScene() const;

	/* Time */
	GLuint getFramesPassed();
	GLfloat getStartupAnimationTime() const;

	/**
	 * Store shaders.
	 *
	 * T can be:
	 *
	 * GL_VERTEX_SHADER
	 * GL_TESS_CONTROL_SHADER
	 * GL_TESS_EVALUATION_SHADER
	 * GL_GEOMETRY_SHADER
	 * GL_FRAGMENT_SHADER
	 */

	template <GLuint T> core::Shader* storeShader(const std::string& shaderPath);
	template <GLuint T> core::Shader* storeShader(const std::string& shaderPath,
	      const std::string& shaderSource);

	core::Program* storeProgram(
	   const std::string& name,
	   const std::vector<core::Shader*>& shaders,
	   GLboolean skipLinking = GL_FALSE);

	/* Store textures */
	core::Texture2D* storeTexture(
	   const std::string& texturePath,
	   framework::eCompression compression = framework::eCompression::eNone);

	core::Texture2DRenderable* storeTextureRenderable();

	core::Texture2DRenderableDynamic* storeTextureDynamic(
	   const std::string& fragmentShaderPath);

	core::Texture3D* storeTexture3D(
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
	   pMoveable followed = pMoveable());

	pLightPoint storeLightPoint(
	   glm::vec3 position,
	   glm::vec4 color,
	   pMoveable followed = pMoveable());

	pLightDirectional storeLightDirectional(
	   glm::vec3 position,
	   glm::quat rotation,
	   glm::vec4 color,
	   pMoveable followed = pMoveable());

	/* Store text */
	pText storeText(
	   std::string content,
	   std::string fontName,
	   glm::vec2 position,
	   GLfloat scale = 1.0,
	   glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0),
	   eTextEffect effect = eTextEffect::eNone);

	/* Store sampler */
	core::Sampler* storeSO(GLint textureUnit);

	/* Store vertex array objects */
	core::VertexArray* storeVAO(framework::IReloadable* user = nullptr);
    core::VertexBufferBasic* storeVBO(core::VertexArray* vao, framework::TerrainConstructor* constructor,
            GLint density,
            GLfloat gap,
            std::vector<GLuint>& indices);
    core::VertexBufferBasic* storeVBO(core::VertexArray* vao, core::VertexBufferBasic* buffer);
    core::IndexBufferBasic* storeIBO(core::VertexArray* vao, std::vector<GLuint>& data);
    core::IndexBufferBasic* storeIBO(core::VertexArray* vao, core::IndexBufferBasic*buffer);

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
	                       framework::FILLWAVE_ENDLESS);

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
	framework::TextureSystem* getTextureSystem() const;

 private:
	struct EngineImpl;
	std::unique_ptr<EngineImpl> mImpl;
};
} /* fillwave */

#endif /*  FILLWAVE_H_ */

/* Header for class com_example_runningremote_RunningRemote */
