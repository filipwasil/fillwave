/*
 * Fillwave.h
 *
 *  Created on: Feb 10, 2014
 *      Author: Filip Wasil
 */

#ifndef FILLWAVE_H_
#define FILLWAVE_H_


/* Callbacks */
#include <fillwave/actions/TimedMoveCallback.h>
#include <fillwave/actions/TimedRotateCallback.h>
#include <fillwave/actions/TimedScaleCallback.h>
#include <fillwave/actions/FPSCallback.h>
#include <fillwave/actions/TimedEmiterUpdateCallback.h>
#include <fillwave/actions/LoopCallback.h>
#include <fillwave/actions/SequenceCallback.h>

/* Events */
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

/* effects */
#include <fillwave/effects/Fog.h>
#include <fillwave/effects/BoostColor.h>
#include <fillwave/effects/TextureOnly.h>

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

/* Particles */
#include <fillwave/particles/Impostor.h>
#include <fillwave/particles/EmiterPointGPU.h>
#include <fillwave/particles/EmiterPointCPU.h>

/* Terrain */
#include <fillwave/terrain/Terrain.h>
#include <fillwave/terrain/MeshTerrain.h>

/* Extras */
#include <fillwave/extras/Debugger.h>

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
			GLfloat xPosition = -0.95,
			GLfloat yPosition = 0.95,
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
	manager::LightManager* getLightManager() const;

	const fScene* getModelFromFile(std::string path); /* xxx remove */

	/* Scene */
	void setCurrentScene(pScene scene);
	pScene getCurrentScene() const;

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
	pTexture storeTexture(const std::string& texturePath, const GLuint& mapType =
	FILLWAVE_TEXTURE_TYPE_NONE, loader::eCompression compression =
			loader::eCompression::eNone);

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
			GLfloat startingPositionX,
			GLfloat startingPositionY,
			GLfloat scale = 1.0,
			glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0),
			eTextEffect effect = eTextEffect::eNone);

	/* Store sampler */
	pSampler storeSO(GLint textureUnit);

	/* Store vertex array objects */
	pVertexArray storeVAO(models::Reloadable* user = nullptr);

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

	/* Inputs - insert */
	void insertInput(actions::EventType& event);
	void insertResizeScreen(GLuint width, GLuint height);

	/* Inputs - register */
	void registerCallback(actions::Callback* callback);

	/* Inputs - unregister */
	void unregisterCallback(actions::Callback* callback);

	/* Inputs - clear */
	void clearCallback(actions::Callback* callback);
	void clearCallbacks(eEventType eventType);

	void reload();

	GLboolean isDR() const;
private:
	struct EngineImpl;
	std::unique_ptr<EngineImpl> mImpl;
};
} /* fillwave */

#endif /*  FILLWAVE_H_ */

/* Header for class com_example_runningremote_RunningRemote */
