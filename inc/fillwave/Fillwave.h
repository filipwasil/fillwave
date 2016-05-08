/*
 * Fillwave.h
 *
 *  Created on: Feb 10, 2014
 *      Author: Filip Wasil
 */

#ifndef FILLWAVE_H_
#define FILLWAVE_H_

#include <fillwave/space/Scene.h>

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
namespace framework {
class Focusable;
}
namespace core {
/* All buffers should be there */
//core::VertexBufferBasic
//core::IndexBuffer
struct VertexParticleGPU;
struct VertexPosition;
struct VertexFloat;
class VertexBufferParticles;
class VertexBufferParticlesGPU;
class VertexBufferFloat;
class VertexBufferPosition;
}

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
	void setCurrentScene(puScene&& scene);
	framework::Scene* getCurrentScene() const;

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
	framework::LightSpot* storeLightSpot(
	   glm::vec3 position,
	   glm::quat rotation,
	   glm::vec4 color,
	   framework::Moveable* followed = nullptr);

	framework::LightPoint* storeLightPoint(
	   glm::vec3 position,
	   glm::vec4 color,
	   framework::Moveable* followed = nullptr);

	framework::LightDirectional* storeLightDirectional(
	   glm::vec3 position,
	   glm::quat rotation,
	   glm::vec4 color,
	   framework::Moveable* followed = nullptr);

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
	core::VertexArray* storeVAO(framework::IReloadable* user,
	                            core::VertexArray* vao = nullptr);

	/* Store one buffer for one VAO */
	template<class T, typename ...S>
	T* storeBuffer(core::VertexArray* vao, S ... p) {
		return storeBufferInternal(vao, p...);
	}

	/* Enables to store many buffers in one VAO */
	template<class T, typename ...S>
	T* storeBuffers(core::VertexArray* vao, size_t idx, S ... p) {
		return storeBuffersInternal(vao, idx, p...);
	}

	/* Buffering */
	void removeBuffer(core::VertexArray* vao); // xxx any idea of generic class ?
	void removeBufferIndex(core::VertexArray* vao);
	void removeBufferIndexParticles(core::VertexArray* vao);
	void removeBufferBasic(core::VertexArray* vao);
	void removeBufferText(core::VertexArray* vao);

	/* Clear */
	void clearText(pText text);
	void clearLight(framework::LightSpot *light);
	void clearLight(framework::LightDirectional *light);
	void clearLight(framework::LightPoint *light);
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
	void dropFocus(framework::IFocusable* focusable = nullptr);

	/* Inputs */
	void insertInput(framework::EventType& event);
	void insertResizeScreen(GLuint width, GLuint height);
	void registerCallback(const framework::Callback& callback,
	                      framework::IFocusable* focusable = nullptr);
	void unregisterCallback(framework::CallbackId Id);
	void unregisterCallbacks(eEventType eventType);
	void unregisterCallbacks();

	void reload();

	framework::LightSystem* getLightSystem() const;
	framework::TextureSystem* getTextureSystem() const;

 private:
	struct EngineImpl;
	std::unique_ptr<EngineImpl> mImpl;
	core::VertexBufferBasic* storeBufferInternal(core::VertexArray* vao,
	      framework::TerrainConstructor* constructor, GLint density, GLfloat gap,
	      std::vector<GLuint>& indices);
	core::VertexBufferBasic* storeBufferInternal(core::VertexArray* vao,
	      std::vector<core::VertexBasic>& data);
	core::VertexBufferText* storeBufferInternal(core::VertexArray* vao,
	      const std::vector<GLfloat>& data, const std::vector<GLfloat>& textureCoords);
	core::VertexBufferParticlesGPU* storeBuffersInternal(core::VertexArray* vao,
	      size_t idx, std::vector<core::VertexParticleGPU>& particles);
	core::VertexBufferParticles* storeBufferInternal(core::VertexArray* vao,
	      std::vector<GLfloat>& velocities, std::vector<GLfloat>& positions,
	      std::vector<GLfloat>& times);
	core::VertexBufferDebug* storeBufferInternal(core::VertexArray* vao,
	      GLfloat scale);
	core::VertexBufferFloat* storeBufferInternal(core::VertexArray* vao,
	      std::vector<core::VertexFloat>& data);
	core::VertexBufferPosition* storeBufferInternal(core::VertexArray* vao,
	      std::vector<core::VertexPosition>& data);
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
	core::VertexBufferBasic* storeBufferInternal(core::VertexArray* vao,
	      const aiMesh* shape, framework::Animator* animator);
	core::IndexBuffer* storeBufferInternal(core::VertexArray* vao,
	                                       const aiMesh* shape);
#endif
	core::IndexBuffer* storeBufferInternal(core::VertexArray* vao,
	                                       const std::vector<GLuint>& data);
	core::IndexBuffer* storeBufferInternal(core::VertexArray* vao, GLuint elements);
};

} /* fillwave */

#endif /*  FILLWAVE_H_ */

/* Header for class com_example_runningremote_RunningRemote */
