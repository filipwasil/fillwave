/*
 * Fillwave.h
 *
 *  Created on: Feb 10, 2014
 *      Author: Filip Wasil
 */

#ifndef FILLWAVE_H_
#define FILLWAVE_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

/* core */
#include <fillwave/core/rendering/FramebufferGeometry.h>
#include <fillwave/core/rendering/Texture2DRenderableDynamic.h>
#include <fillwave/core/buffers/PixelBuffer.h>

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

/* Particles */
#include <fillwave/particles/Impostor.h>
#include <fillwave/particles/EmiterPointGPU.h>
#include <fillwave/particles/EmiterPointCPU.h>

/* Terrain */
#include <fillwave/terrain/Terrain.h>
#include <fillwave/terrain/MeshTerrain.h>

/* Loaders */
#include <fillwave/loaders/FileLoader.h>
#include <fillwave/loaders/ProgramLoader.h>

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

struct ANativeActivity;

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

	manager::LightManager* getLightManager();

	/* Scene */
	void setCurrentScene(pScene scene);

	pScene getCurrentScene();

	/* Time */
	GLuint getFramesPassed();

	GLfloat getStartupAnimationTime();

	/* Store shaders */
//   pShader  storeShaderCompute(const std::string& shaderPath);
	pShader storeShaderFragment(const std::string& shaderPath);
	pShader storeShaderVertex(const std::string& shaderPath);

//   pShader  storeShaderCompute(const std::string& shaderPath, std::string& shaderSource);
	pShader storeShaderFragment(
			const std::string& shaderPath,
			const std::string& shaderSource);
	pShader storeShaderVertex(
			const std::string& shaderPath,
			const std::string& shaderSource);

	pProgram storeProgram(
			const std::string& name,
			const std::vector<pShader>& shaders,
			GLboolean skipLinking = GL_FALSE);

	/* Store textures */
	pTexture storeTexture(const std::string& texturePath, const GLuint& mapType =
			FILLWAVE_TEXTURE_TYPE_NONE, loader::eCompression compression =
			loader::eCompression::none);

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
			pEntity entity = pEntity());

	pLightPoint storeLightPoint(
			glm::vec3 position,
			glm::vec4 color,
			pEntity entity = pEntity());

	pLightDirectional storeLightDirectional(
			glm::vec3 position,
			glm::quat rotation,
			glm::vec4 color,
			pEntity entity = pEntity());

	/* Store text */
	pText storeText(
			std::string content,
			std::string fontName,
			GLfloat startingPositionX,
			GLfloat startingPositionY,
			GLfloat scale = 1.0,
			glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0),
			eTextEffect effect = eTextEffect::none);

#ifdef __ANDROID__
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

	pSampler storeSO(GLint textureUnit);

	pVertexArray storeVAO(models::Reloadable* user = nullptr);

	void clearText(pText text);
	void clearLight(pLightSpot light);
	void clearLight(pLightDirectional);
	void clearLight(pLightPoint light);
	void clearLights();

	/* Picking */
	void pick(GLuint x, GLuint y);

	/* Screen */
	glm::ivec2 getScreenSize();

	/* Log */
	void log();

	/* Screenshot */
	void captureFramebufferToFile(const std::string& name);
	void captureFramebufferToBuffer(
			GLubyte* buffer,
			GLint* sizeInBytes,
			GLuint format = GL_RGBA,
			GLint bytesPerPixel = 4);

	/* File system */
	std::string getExecutablePath();

	/* Post processing */
	void addPostProcess(const std::string& fragmentShaderPath, GLfloat lifeTime =
			FILLWAVE_ENDLESS);

	/* Inputs - setFocus */
	void setFocusKey(pEntity entity);
	void setFocusMouseButton(pEntity entity);
	void setFocusScroll(pEntity entity);
	void setFocusChar(pEntity entity);
	void setFocusCharMods(pEntity entity);
	void setFocusCursorEnter(pEntity entity);
	void setFocusCursorPosition(pEntity entity);

	/* Inputs - getFocus */
	pEntity getFocusKey();
	pEntity getFocusMouseButton();
	pEntity getFocusScroll();
	pEntity getFocusChar();
	pEntity getFocusCharMods();
	pEntity getFocusCursorEnter();
	pEntity getFocusCursorPosition();
	pEntity getFocusTouchScreen();

	/* Inputs - insert */
	void insertResizeScreen(GLuint width, GLuint height);
	void insertInputKey(actions::KeyboardEvent& event);
	void insertInputMouseButton(actions::MouseButtonEvent& event);
	void insertInputScroll(actions::ScrollEvent & event);
	void insertInputCharacter(actions::CharacterEvent& event);
	void insertInputCharacterMods(actions::CharacterModsEvent& event);
	void insertInputCursorEnter(actions::CursorEnterEvent& event);
	void insertInputCursorPosition(actions::CursorPositionEvent& event);
	void insertInputTouchScreen(actions::TouchEvent& event);

	/* Inputs - register */
	void registerTimeCallback(actions::EngineCallback* callback);
	void registerKeyCallback(actions::EngineCallback* callback);
	void registerMouseButtonCallback(actions::EngineCallback* callback);
	void registerScrollCallback(actions::EngineCallback* callback);
	void registerCharCallback(actions::EngineCallback* callback);
	void registerCharModsCallback(actions::EngineCallback* callback);
	void registerCursorEnterCallback(actions::EngineCallback* callback);
	void registerCursorPositionCallback(actions::EngineCallback* callback);
	void registerTouchScreenCallback(actions::EngineCallback* callback);

	/* Inputs - unregister */
	void unregisterTimeCallback(actions::EngineCallback* callback);
	void unregisterKeyCallback(actions::EngineCallback* callback);
	void unregisterMouseButtonCallback(actions::EngineCallback* callback);
	void unregisterScrollCallback(actions::EngineCallback* callback);
	void unregisterCharCallback(actions::EngineCallback* callback);
	void unregisterCharModsCallback(actions::EngineCallback* callback);
	void unregisterCursorEnterCallback(actions::EngineCallback* callback);
	void unregisterCursorPositionCallback(actions::EngineCallback* callback);
	void unregisterTouchScreenCallback(actions::EngineCallback* callback);

	/* Inputs - clear */
	void clearTimeCallbacks();
	void clearKeyCallbacks();
	void clearMouseButtonCallbacks();
	void clearScrollCallbacks();
	void clearCharCallbacks();
	void clearCharModsCallbacks();
	void clearCursorEnterCallbacks();
	void clearCursorPositionCallbacks();
	void clearTouchScreenCallbacks();

	void reload();

	/* Asset loader */
	const fScene* getModelFromFile(std::string path);

	GLboolean isDR();
private:
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

	/* Startup */
	GLfloat mStartupTime;
	pTexture mStartupTexture;
	const GLfloat mStartupTimeLimit = 8.0f;
	puPostProcessingPass mPostProcessingPassStartup;

	/* Techniques */
	GLboolean mIsDR; /* Deferred rendering */
	GLboolean mIsAO; /* Ambient occlusion */
	GLboolean mISOQ; /* Occlusion query */

	/* Scene */
	pScene mScene;

	glm::vec3 mBackgroundColor;

	/* Loaders */
	loader::FontLoader mFontLoader;
	loader::FileLoader mFileLoader;
	loader::ProgramLoader mProgramLoader;

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

	/* DLC - Uniform location cache */
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
	GLfloat mTimeFactor;
	GLuint mFrameCounter;
	pText mFPSText;
	actions::FPSCallback* mTextFPSCallback;

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
	void reloadPickingBuffer();

	void reloadGeometryBuffer();
};
} /* fillwave */

#endif /*  FILLWAVE_H_ */

/* Header for class com_example_runningremote_RunningRemote */
