/*
 * Fillwave.cpp
 *
 *  Created on: Feb 10, 2014
 *      Author: Filip Wasil
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2015] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * filip.wasil@gmail.com
 *
 */

/* Plarform specific */
#include <fillwave/loaders/AndroidLoader.h>

/* Debug */
#include <fillwave/extras/Log.h>

/* Profiling */
#include <fillwave/Profiler.h>

/* Fillwave */

#include <fillwave/Fillwave.h>

/* Models */
#include <fillwave/models/shapes/BoxOcclusion.h>

/* Assets */
#include <fillwave/Assets.h>

/* Stdlib */
#include <fstream>

FLOGINIT("Engine", FERROR | FFATAL | FDEBUG | FINFO)

namespace fillwave {

#ifdef __ANDROID__

Engine::Engine(std::string rootPath)
:mFrameCounter(0),
 mTimeFactor(1.0),
 mBackgroundColor(0.1,0.1,0.1),
 mFileLoader(rootPath),
 mStartupTime(0.0f),
 mIsDR(GL_FALSE),
 mIsAO(GL_FALSE),
 mISOQ(GL_FALSE) {
   init();
}

Engine::Engine(ANativeActivity* activity)
:mFrameCounter(0),
 mTimeFactor(1.0),
 mBackgroundColor(0.1,0.1,0.1),
 mFileLoader(activity->internalDataPath),
 mStartupTime(0.0f),
 mIsDR(GL_FALSE),
 mIsAO(GL_FALSE),
 mISOQ(GL_FALSE) {

 loader::androidSetActivity(activity);

 loader::androidExtractAll();

#else
Engine::Engine(GLint argc, GLchar* const argv[])
:mFrameCounter(0),
 mTimeFactor(1.0),
 mBackgroundColor(0.1,0.1,0.1),
 mFileLoader((std::string(argv[0]).substr(0,std::string(argv[0]).find_last_of(FILLWAVE_OS_SEPRATOR)))),
 mStartupTime(0.0f),
 mIsDR(GL_FALSE),
 mIsAO(GL_FALSE),
 mISOQ(GL_TRUE) {
#endif
   init();
}

void Engine::configureTime(GLfloat timeFactor) {
   mTimeFactor = timeFactor;
}

Engine::~Engine() {
   mTextManager.clear();
   mFontManager.clear();
   mPostProcessingPasses.clear();
   mTexturesDynamic.clear();
   if (mScene) {
      mScene.reset();
   }
}

void Engine::configureBackgroundColor(glm::vec3 color) {
   mBackgroundColor = color;
}

inline void Engine::drawClear() {
   glClearColor(mBackgroundColor.x, mBackgroundColor.y, mBackgroundColor.z, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

inline void Engine::drawScene(GLfloat time) {

   evaluateTime(time);

   if (mPostProcessingPasses.size()) {
      auto _compare_function =
            [](common::PostProcessingPass& pass) -> bool {return pass.isFinished();};
      auto _begin = mPostProcessingPasses.begin();
      auto _end = mPostProcessingPasses.end();

      core::Texture2DRenderableDynamic* textureNext;
      core::Program* programNext;

      core::Texture2DRenderableDynamic* textureCurrent =
            (*_begin).getFrame().get();

      core::Program* programCurrent;

      drawClear();

      textureCurrent->bindForWriting();

      drawSceneCore();

      for (auto it=_begin; it!=_end; it++) {

         auto next = it + 1;

         if (next != _end) {

            textureNext = (*next).getFrame().get();
            programNext = (*next).getProgram().get();
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

inline void Engine::drawSceneCore() {
   if (mIsDR) {
      drawSceneCoreDR();
   } else {
      drawSceneCoreFR();
   }
}


inline void Engine::drawSceneCoreFR() {
   if (mISOQ) {
      drawOcclusionPass();
   }
   drawClear();
   mScene->drawSkybox();
   glClear(GL_DEPTH_BUFFER_BIT);
   mScene->draw();
}

inline void Engine::drawSceneCoreDR() {
   if (mISOQ) {
      drawOcclusionPass();
   }
   drawClear();
   mGBuffer->setAttachments(); //bind for geom pass
   drawGeometryPass();
   drawAOPass();
   drawColorPass();
   mDebugger->renderGeometryBuffer(mWindowWidth, mWindowHeight, mDeferredColorAttachments, mGBuffer.get());
}

void Engine::draw(GLfloat time) {
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
void Engine::drawLines(GLfloat time) {

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

void Engine::drawPoints(GLfloat time) {

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

void Engine::drawTexture(core::Texture* t, core::Program* p) {
   p->use();
   t->bind(FILLWAVE_DIFFUSE_UNIT);
   p->uniformPush("uPostProcessingSampler", FILLWAVE_DIFFUSE_UNIT);
   glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);
   t->unbind();
   core::Program::disusePrograms();
}

void Engine::drawTexture(core::Texture* t) {
   mProgramTextureLookup->use();
   mProgramTextureLookup->uniformPush("uPostProcessingSampler", FILLWAVE_DIFFUSE_UNIT);
   t->bind(FILLWAVE_DIFFUSE_UNIT);
   glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);
   t->unbind();
}

inline void Engine::drawGeometryPass() {
   glDepthMask(GL_TRUE);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
   glDisable(GL_BLEND);
   mScene->drawDR();
   glDepthMask(GL_FALSE);
}

inline void Engine::drawOcclusionPass() {
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

inline void Engine::drawAOPass() {
   mAOGeometryBuffer->bindForWriting();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   mScene->drawAOG();

   mAOColorBuffer->bindForWriting();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   mAOGeometryBuffer->bind(FILLWAVE_POSITION_ATTACHMENT);
   mScene->drawAOC();
}

inline void Engine::drawColorPassBegin() {
   mGBuffer->setAttachments();

   glDisable(GL_DEPTH_TEST);
   glEnable(GL_BLEND);
   glBlendEquation(GL_FUNC_ADD);
   glBlendFunc(GL_ONE, GL_ONE);

   mGBuffer->setAttachmentSummaryForWriting();
   mGBuffer->bindAttachments();
}

inline void Engine::drawColorPass() {
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

inline void Engine::drawAmbientPass() {
   mProgramDRAmbient->use();
   core::Uniform::push(uULCDRAAmbientGlobal, mScene->getAmbient());
   glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);
}

inline void Engine::drawDepthlessPass() {
   mProgramDRDepthless->use();
   glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);
}

inline void Engine::drawLightsSpotPass(GLint& textureUnit) {
   for (GLint i=0; i<mLightManager->getLightsSpotHowMany(); i++) {

      mProgramDRSpotLight->use();
      mLightManager->updateDeferredBufferSpot(i, mProgramDRSpotLight.get(), textureUnit++);

      core::Uniform::push(mULCCameraPositionSpot, mScene->getCamera()->getTranslation());
      core::Uniform::push(mULCIsAOSpot, mIsAO ? 1 : 0);
//xxx   When runtime change is not needed this is sufficient:
//      if (mIsAO) {
//         core::Uniform::push(mULCIsAOSpot, 1);
//      }
//      core::Uniform::push(mULCAmbientIntensitySpot, 0.2f);
//      core::Uniform::push(mULCShadowUnitSpot, textureUnit++);

      glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);
   }
}

inline void Engine::drawLightsDirectionalPass(GLint& textureUnit) {
   for (GLint i=0; i<mLightManager->getLightsDirectionalHowMany(); i++) {

      mProgramDRDirecionalLight->use();
      mLightManager->updateDeferredBufferDirectional(i, mProgramDRDirecionalLight.get(), textureUnit++);

      core::Uniform::push(mULCCameraPositionDirectional, mScene->getCamera()->getTranslation());
      core::Uniform::push(mULCIsAODirectional, mIsAO ? 1 : 0);
//      core::Uniform::push(mULCAmbientIntensityDirectional, 0.2f);
//xxx   When runtime change is not needed this is sufficient:
//      if (mIsAO) {
//         core::Uniform::push(mULCIsAODirectional, 1);
//      }
//      core::Uniform::push(mULCShadowUnitDirectional, textureUnit++);

      glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);
   }
}

inline void Engine::drawLightsPointPass(GLint& textureUnit) {
   glEnable(GL_STENCIL_TEST);

   for (GLint i=0; i<mLightManager->getLightsPointHowMany(); i++) {
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
      mLightManager->updateDeferredBufferPoint(i, mProgramDRPointLight.get(), textureUnit++);

      core::Uniform::push(mULCCameraPositionPoint, camera->getTranslation());
      core::Uniform::push(mULCMVPPoint,
            camera->getViewProjection() * glm::translate(glm::mat4(1.0),
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


inline void Engine::drawColorPassEnd() {
   mGBuffer->setAttachmentSummaryForReading();
   glBlitFramebuffer(0, 0, mWindowWidth, mWindowHeight,
                     0, 0, mWindowWidth, mWindowHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

inline void Engine::evaluateStartupAnimation(GLfloat time) {

   drawClear();

   core::Texture2DRenderableDynamic* tex = mPostProcessingPassStartup->getFrame().get();

   tex->bindForWriting();

   drawTexture(mStartupTexture.get());

   core::Framebuffer::bindScreenFramebuffer();

   tex->draw(time);

   drawTexture(tex, mPostProcessingPassStartup->getProgram().get());

   mPostProcessingPassStartup->checkTime(time);
}

inline void Engine::evaluateShadowMaps() {

   glDepthMask(GL_TRUE);

   mLightManager->updateLightEntities();

   GLint currentTextureUnit = FILLWAVE_SHADOW_FIRST_UNIT;

   core::Texture2DRenderable* light2DTexture;
   for (GLint i=0; i<mLightManager->getLightsSpotHowMany(); i++) {
      space::CameraPerspective camera = *(mLightManager->getLightSpot(i)->getShadowCamera().get());
      light2DTexture = mLightManager->getLightSpot(i)->getShadowTexture().get();
      light2DTexture->bindForWriting();
      light2DTexture->bind(currentTextureUnit++);
      glClearColor (0.0, 0.0, 0.0, 1.0);
      glClear(GL_DEPTH_BUFFER_BIT);
      mScene->drawDepth(camera);
   }

   for (GLint i=0; i<mLightManager->getLightsDirectionalHowMany(); i++) {
      space::CameraOrthographic camera = *(mLightManager->getLightDirectional(i)->getShadowCamera().get());
      light2DTexture = mLightManager->getLightDirectional(i)->getShadowTexture().get();
      light2DTexture->bindForWriting();
      light2DTexture->bind(currentTextureUnit++);
      glClearColor (0.0, 0.0, 0.0, 1.0);
      glClear(GL_DEPTH_BUFFER_BIT);
      mScene->drawDepth(camera);
   }

   for (GLint i=0; i<mLightManager->getLightsPointHowMany(); i++) {
      space::LightPoint* lightPoint = mLightManager->getLightPoint(i).get();
      core::Texture3DRenderable* light3DTexture = lightPoint->getShadowTexture().get();
      glm::vec3 lightPosition(lightPoint->getTranslation());
      light3DTexture->bindForWriting();
      light3DTexture->bind(currentTextureUnit);
      for (GLint j=GL_TEXTURE_CUBE_MAP_POSITIVE_X; j <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z ;j++) {
         space::CameraPerspective camera = *(lightPoint->getShadowCamera(j).get());
         light3DTexture->setAttachmentFace(j, GL_COLOR_ATTACHMENT0);
         glClearColor (0.0, 0.0, 0.0, 1.0);
         glClear(GL_DEPTH_BUFFER_BIT);
         mScene->drawDepthColor(camera, lightPosition);
      }
      currentTextureUnit++;
   }
   core::Framebuffer::bindScreenFramebuffer();
}

inline void Engine::evaluateDynamicTextures(GLfloat timeExpiredInSeconds) {
   for (auto& it : mTexturesDynamic) {
      it->bindForWriting();
      it->draw(timeExpiredInSeconds);
   }
   core::Framebuffer::bindScreenFramebuffer();
}

inline void Engine::evaluateTime(GLfloat timeExpiredInSeconds) {
   if (mTimeFactor) {
      actions::TimeEventData data;
      data.mTimePassed = timeExpiredInSeconds;
      actions::TimeEvent timeEvent(data);
      runCallbacks(mTimeCallbacks, &timeEvent);
      mScene->handleHierarchyEvent(&timeEvent);
   }
}

inline void Engine::evaluateDebugger() {
   GLint mCurentTextureUnit = 0;
   GLint id = 0;
   switch (mDebugger->getState()) {
      case eDebuggerState::lightsSpot:
         mCurentTextureUnit = 0;
         for (GLint i=0; i<mLightManager->getLightsSpotHowMany();i++) {
            space::CameraPerspective cameraP =  *(mLightManager->getLightSpot(i)->getShadowCamera().get());
            mDebugger->renderFromCamera(cameraP, mCurentTextureUnit++);//xxx make more flexible
         }
         for (GLint i=0; i<mLightManager->getLightsDirectionalHowMany();i++) {
            space::CameraOrthographic cameraO = *(mLightManager->getLightDirectional(i)->getShadowCamera().get());
            mDebugger->renderFromCamera(cameraO, mCurentTextureUnit++);//xxx make more flexible
         }
         mCurentTextureUnit = 0;
         for (GLint i=0; i<mLightManager->getLightsSpotHowMany();i++) {
            mDebugger->renderDepthPerspective(mCurentTextureUnit++);
         }
         for (GLint i=0; i<mLightManager->getLightsDirectionalHowMany();i++) {
            mDebugger->renderDepthOrthographic(mCurentTextureUnit++);
         }
         break;
      case eDebuggerState::lightsSpotDepth:
         mCurentTextureUnit = 0;
         for (GLint i=0; i<mLightManager->getLightsSpotHowMany();i++) {
            mDebugger->renderDepthPerspective(mCurentTextureUnit++);
         }
         for (GLint i=0; i<mLightManager->getLightsDirectionalHowMany();i++) {
            mDebugger->renderDepthOrthographic(mCurentTextureUnit++);
         }
         break;
      case eDebuggerState::lightsSpotColor:
         mCurentTextureUnit = 0;
         for (GLint i=0; i<mLightManager->getLightsSpotHowMany();i++) {
            space::CameraPerspective cameraP =  *(mLightManager->getLightSpot(i)->getShadowCamera().get());
            mDebugger->renderFromCamera(cameraP, mCurentTextureUnit++);//xxx make more flexible
         }
         for (GLint i=0; i<mLightManager->getLightsDirectionalHowMany();i++) {
            space::CameraOrthographic cameraO =  *(mLightManager->getLightDirectional(i)->getShadowCamera().get());
            mDebugger->renderFromCamera(cameraO, mCurentTextureUnit++);//xxx make more flexible
         }
         break;
      case eDebuggerState::lightsPoint:
         break;
      case eDebuggerState::lightsPointDepth: // only light 0
         break;
      case eDebuggerState::lightsPointColor:
         for (GLint j=0; j<mLightManager->getLightsPointHowMany();j++) {
            for (int i=GL_TEXTURE_CUBE_MAP_POSITIVE_X; i<=GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; i++) {
               space::CameraPerspective cameraPF =  *(mLightManager->getLightPoint(j)->getShadowCamera(i).get());
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

glm::ivec4 Engine::pickingBufferGetColor(GLubyte* data, GLuint x, GLuint y) {
   y = mWindowHeight - y;
   GLuint id, r, g, b, a;

   if (x < mWindowWidth && y < mWindowHeight) {
       id = (x + y * mWindowWidth) * 4;
       b = data[id];
       g = data[id + 1];
       r = data[id + 2];
       a = data[id + 3];
   }
   return glm::ivec4( r, g, b, a);
}

inline void Engine::drawText() {
   for (auto& it : mTextManager) {
      it->draw();
   }
}

pLightSpot Engine::storeLightSpot(glm::vec3 position,
                                  glm::quat rotation,
                                  glm::vec4 color,
                                  pEntity entity) {
   return mLightManager->addLightSpot(mTextureManager->getShadow2D(mWindowWidth, mWindowHeight),
                                      position,
                                      rotation,
                                      color,
                                      entity);
}

pLightPoint Engine::storeLightPoint(glm::vec3 position,
        glm::vec4 color,
        pEntity entity) {
   return mLightManager->addLightPoint(mTextureManager->getShadow3D(mWindowWidth, mWindowHeight),
         position,
         color,
         entity);
}

pLightDirectional Engine::storeLightDirectional(glm::vec3 position,
      glm::quat rotation,
      glm::vec4 color,
      pEntity entity) {
   return mLightManager->addLightDirectional(mTextureManager->getShadow2D(mWindowWidth, mWindowHeight),
         position,
         rotation,
         color,
         entity);
}

inline pShader Engine::storeShader(const std::string& shaderPath, const GLuint& shaderType) {
   return mShaderManager->add(shaderPath, shaderType);}

inline pShader  Engine::storeShader(const std::string& shaderName, const GLuint& shaderType, const std::string& shaderSource) {
   return mShaderManager->add(shaderName, shaderType, shaderSource);
}

pShader Engine::storeShaderFragment(const std::string& shaderPath) {
   return mShaderManager->add(shaderPath, GL_FRAGMENT_SHADER);}

pShader Engine::storeShaderFragment(const std::string& shaderPath, const std::string& shaderSource) {
   return mShaderManager->add(shaderPath, GL_FRAGMENT_SHADER, shaderSource);}

pShader Engine::storeShaderVertex(const std::string& shaderPath) {
   return mShaderManager->add(shaderPath, GL_VERTEX_SHADER);}

pShader Engine::storeShaderVertex(const std::string& shaderPath, const std::string& shaderSource) {
   return mShaderManager->add(shaderPath, GL_VERTEX_SHADER, shaderSource);}

pProgram Engine::storeProgram(const std::string& name, const std::vector<pShader>& shaders, GLboolean skipLinking) {
   return mProgramManager->add(name, shaders, skipLinking);
}

pTexture Engine::storeTexture(const std::string& texturePath, const GLuint& mapType) {
   return mTextureManager->get(texturePath, mapType);
}

pTexture2DRenderableDynamic Engine::storeTextureDynamic(const std::string& fragmentShaderPath) {
   const std::string path = fragmentShaderPath;
   pProgram program = mProgramLoader.getQuadCustomFragmentShader(this, fragmentShaderPath);
   pTexture2DRenderableDynamic t = mTextureManager->getDynamic(path, program, glm::ivec2(mWindowWidth,mWindowHeight));
   mTexturesDynamic.push_back(t);
   return t;
}

pTexture3D Engine::storeTexture3D(const std::string& posX,
                                  const std::string& negX,
                                  const std::string& posY,
                                  const std::string& negY,
                                  const std::string& posZ,
                                  const std::string& negZ) {
   return mTextureManager->get(posX,
                               negX,
                               posY,
                               negY,
                               posZ,
                               negZ);
}

void Engine::configureDebugger(eDebuggerState state){
   mDebugger->setState(state);
}

/* Engine callbacks - run */

inline void Engine::runCallbacks(std::vector<actions::EngineCallback*>& callbacks, actions::EventType* event) {
   Engine* engine = this;
   std::for_each(callbacks.begin(), callbacks.end(), [engine, event](actions::EngineCallback* e){ e->perform(engine, event); });
}

/* Engine callbacks - clear */

inline void Engine::clearCallbacks(std::vector<actions::EngineCallback*>& callbacks) {
   std::for_each(callbacks.begin(), callbacks.end(), [](actions::EngineCallback* e){ delete e; });
   callbacks.clear();
}

/* Engine callbacks - unregister */

void Engine::unregisterCallback(std::vector<actions::EngineCallback*>& callbacks, actions::EngineCallback* callback) {
   auto _compare_function = [callback](const actions::EngineCallback* e) -> bool { bool found = (e == callback); if (found) delete callback; return found; };
   auto _begin = callbacks.begin();
   auto _end = callbacks.end();
   auto it = std::remove_if(_begin, _end, _compare_function);
   callbacks.erase(it, _end);
}

/* Inputs - insert */

void Engine::insertInputKey(fillwave::actions::KeyboardEvent& event) {
   if (getFocusKey()) {
      getFocusKey()->handlePrivateEvent(&event);
   }
   runCallbacks(mKeyCallbacks, &event);
}

void Engine::insertInputMouseButton(actions::MouseButtonEvent& event) {
   if (getFocusMouseButton()) {
      getFocusMouseButton()->handlePrivateEvent(&event);
   }
   runCallbacks(mMouseButtonCallbacks, &event);
}

void Engine::insertInputScroll(actions::ScrollEvent& event) {
   if (getFocusScroll()) {
      getFocusScroll()->handlePrivateEvent(&event);
   }
   runCallbacks(mScrollCallbacks, &event);
}

void Engine::insertInputCharacter(actions::CharacterEvent& event) {
   if (getFocusChar()) {
      getFocusChar()->handlePrivateEvent(&event);
   }
   runCallbacks(mCharCallbacks, &event);
}

void Engine::insertInputCharacterMods(actions::CharacterModsEvent& event) {
   if (getFocusCharMods()) {
      getFocusCharMods()->handlePrivateEvent(&event);
   }
   runCallbacks(mCharModsCallbacks, &event);
}

void Engine::insertInputCursorEnter(actions::CursorEnterEvent& event) {
   if (getFocusCursorEnter()) {
      getFocusCursorEnter()->handlePrivateEvent(&event);
   }
   runCallbacks(mCursorEnterCallbacks, &event);
}

void Engine::insertInputCursorPosition(actions::CursorPositionEvent& event) {
   if (getFocusCursorPosition()) {
      getFocusCursorPosition()->handlePrivateEvent(&event);
   }
   runCallbacks(mCursorPositionCallbacks, &event);
}

void Engine::insertInputTouchScreen(actions::TouchEvent& event) {
   if (getFocusTouchScreen()) {
      getFocusTouchScreen()->handlePrivateEvent(&event);
   }
   runCallbacks(mTouchScreenCallbacks, &event);
}

/* Engine callbacks - clear */

void Engine::clearTimeCallbacks() {
   clearCallbacks(mTimeCallbacks);
}

void Engine::clearKeyCallbacks() {
   clearCallbacks(mKeyCallbacks);
}

void Engine::clearMouseButtonCallbacks() {
   clearCallbacks(mMouseButtonCallbacks);
}

void Engine::clearScrollCallbacks() {
   clearCallbacks(mScrollCallbacks);
}

void Engine::clearCharCallbacks() {
   clearCallbacks(mCharCallbacks);
}

void Engine::clearCharModsCallbacks() {
   clearCallbacks(mCharCallbacks);
}

void Engine::clearCursorEnterCallbacks() {
   clearCallbacks(mCursorEnterCallbacks);
}

void Engine::clearCursorPositionCallbacks() {
   clearCallbacks(mCursorPositionCallbacks);
}

void Engine::clearTouchScreenCallbacks() {
   clearCallbacks(mTouchScreenCallbacks);
}

/* Engine callbacks - register */

void Engine::registerTimeCallback(actions::EngineCallback* callback) {
   mTimeCallbacks.push_back(callback);
}

void Engine::registerKeyCallback(actions::EngineCallback* callback) {
   mKeyCallbacks.push_back(callback);
}

void Engine::registerMouseButtonCallback(actions::EngineCallback* callback) {
   mMouseButtonCallbacks.push_back(callback);
}

void Engine::registerScrollCallback(actions::EngineCallback* callback) {
   mScrollCallbacks.push_back(callback);
}

void Engine::registerCharCallback(actions::EngineCallback* callback) {
   mCharCallbacks.push_back(callback);
}

void Engine::registerCharModsCallback(actions::EngineCallback* callback) {
   mCharModsCallbacks.push_back(callback);
}

void Engine::registerCursorEnterCallback(actions::EngineCallback* callback) {
   mCursorEnterCallbacks.push_back(callback);
}

void Engine::registerCursorPositionCallback(actions::EngineCallback* callback) {
   mCursorPositionCallbacks.push_back(callback);
}

void Engine::registerTouchScreenCallback(actions::EngineCallback* callback) {
   mTouchScreenCallbacks.push_back(callback);
}

/* Engine callbacks - unregister */
void Engine::unregisterTimeCallback(actions::EngineCallback* callback) {
   unregisterCallback(mTimeCallbacks, callback);
}

void Engine::unregisterKeyCallback(actions::EngineCallback* callback) {
   unregisterCallback(mKeyCallbacks, callback);
}

void Engine::unregisterMouseButtonCallback(actions::EngineCallback* callback) {
   unregisterCallback(mMouseButtonCallbacks, callback);
}

void Engine::unregisterScrollCallback(actions::EngineCallback* callback) {
   unregisterCallback(mScrollCallbacks, callback);
}

void Engine::unregisterCharCallback(actions::EngineCallback* callback) {
   unregisterCallback(mCharCallbacks, callback);
}

void Engine::unregisterCharModsCallback(actions::EngineCallback* callback) {
   unregisterCallback(mCharModsCallbacks, callback);
}

void Engine::unregisterCursorEnterCallback(actions::EngineCallback* callback) {
   unregisterCallback(mCursorEnterCallbacks, callback);
}

void Engine::unregisterCursorPositionCallback(actions::EngineCallback* callback) {
   unregisterCallback(mCursorPositionCallbacks, callback);
}

void Engine::unregisterTouchScreenCallback(actions::EngineCallback* callback) {
   unregisterCallback(mTouchScreenCallbacks, callback);
}

/* Inputs - setFocus */
void Engine::setFocusKey(pEntity entity) {
   mFocusKey = entity;
}

void Engine::setFocusMouseButton(pEntity entity) {
   mFocusMouseButton = entity;
}

void Engine::setFocusScroll(pEntity entity) {
   mFocusScroll = entity;
}

void Engine::setFocusChar(pEntity entity) {
   mFocusChar = entity;
}

void Engine::setFocusCharMods(pEntity entity) {
   mFocusCharMods = entity;
}

void Engine::setFocusCursorEnter(pEntity entity) {
   mFocusCursorEnter = entity;
}

void Engine::setFocusCursorPosition(pEntity entity) {
   mFocusCursorPosition = entity;
}

/* Inputs - getFocus */
pEntity Engine::getFocusKey() {
   return mFocusKey;
}

pEntity Engine::getFocusMouseButton() {
   return mFocusMouseButton;
}

pEntity Engine::getFocusScroll() {
   return mFocusScroll;
}

pEntity Engine::getFocusChar() {
   return mFocusChar;
}

pEntity Engine::getFocusCharMods() {
   return mFocusCharMods;
}

pEntity Engine::getFocusCursorEnter() {
   return mFocusCursorEnter;
}

pEntity Engine::getFocusCursorPosition() {
   return mFocusCursorPosition;
}

pEntity Engine::getFocusTouchScreen() {
   return mFocusTouchScreen;
}

pText Engine::storeText(std::string content,
                        std::string fontName,
                        GLfloat startingPositionX,
                        GLfloat startingPositionY,
                        GLfloat scale,
                        glm::vec4 color,
                        eTextEffect effect) {
   /* Check for the font texture */
   if (not mTextureManager->check(fontName + ".png")) {
      mFontLoader.load(mFileLoader.getRootPath() + fontName);
   }

   pTexture t = mTextureManager->get(fontName + ".png", FILLWAVE_TEXTURE_TYPE_NONE, loader::eFlip::FILLWAVE_TEXTURE_FLIP_VERTICAL);

   Font* font = nullptr;
   for (auto& it : mFontManager) {
      if (it->mName == fontName) {
         font = it.get();
      }
   }

   if (not font) {
      std::ifstream myfile (mFileLoader.getRootPath(fontName + ".meta"));
      if (!myfile.is_open()) {
         FLOG_ERROR("No text added. Could not write to metadata file: %s", (fontName + ".meta").c_str());
         return pText();
      }
      std::string line;
      std::string ASCII, xMin, width, yMin, height, yOffset;
      GLfloat fXMin, fWidth, fYMin, fHeight, fYOffset;
      GLint iASCII;
      Font* newFont = new Font();
      GLint control = 0;
      while (!myfile.eof()){
         getline(myfile, line);
         myfile >> iASCII >> fXMin >> fWidth >> fYMin >> fHeight >> fYOffset;
         newFont->mWidths[iASCII] = fWidth;
         newFont->mOffsets[iASCII] = 1.0 - fHeight - fYOffset;
         if (control++ > 512) { //xxx limit
            FLOG_ERROR("Metadata can not be read for file %s.", (fontName + ".meta").c_str());
            myfile.close();
            delete newFont;
            return pText();
         }
      }
      myfile.close();
      mFontManager.push_back(pFont(newFont));
      font = newFont;
   }

   pText text = pText(new models::Text(content,
                                       t,
                                       startingPositionX,
                                       startingPositionY,
                                       this,
                                       scale,
                                       font,
                                       color,
                                       effect));
   mTextManager.push_back(pText(text));
   return text;
}

void Engine::clearText(pText text) {
   auto _compare_function = [text](pText t) -> bool { return (t == text); };
   auto _begin = mTextManager.begin();
   auto _end = mTextManager.end();
   auto it = std::remove_if(_begin, _end, _compare_function);
   mTextManager.erase(it, _end);
}

void Engine::clearLight(pLightSpot light) {
   mLightManager->removeLight(light);
}

void Engine::clearLight(pLightDirectional light) {
   mLightManager->removeLight(light);
}

void Engine::clearLight(pLightPoint light) {
   mLightManager->removeLight(light);
}

void Engine::clearLights() {
   mLightManager->removeLights();
}

glm::ivec2 Engine::getScreenSize() {
   return glm::ivec2(mWindowWidth, mWindowHeight);
}

void Engine::insertResizeScreen(GLuint width, GLuint height) {
   mWindowWidth = width;
   mWindowHeight = height;
   glViewport(0, 0, mWindowWidth, mWindowHeight);

   mTextureManager->resize(mWindowWidth, mWindowHeight);

   mPickingPixelBuffer->setScreenSize(mWindowWidth, mWindowHeight, 4);

   if (mIsDR) {
      mGBuffer->resize(mWindowWidth, mWindowHeight);
   }

   mProgramDRSpotLight->use();
   core::Uniform::push(mULCScreenSizeSpot, glm::vec2(mWindowWidth, mWindowHeight));

   mProgramDRDirecionalLight->use();
   core::Uniform::push(mULCScreenSizeDirectional, glm::vec2(mWindowWidth, mWindowHeight));

   mProgramDRPointLight->use();
   core::Uniform::push(mULCScreenSizePoint, glm::vec2(mWindowWidth, mWindowHeight));

   mProgramDRDepthless->use();
   core::Uniform::push(mULCDRScreenSize, glm::vec2(mWindowWidth, mWindowHeight));

   mProgramDRAmbient->use();
   core::Uniform::push(uULCDRAScreenSize, glm::vec2(mWindowWidth, mWindowHeight));

   for (auto& it : mTextManager) { //xxx todo optimize to update only VBO
      it->editAspectRatio(this);
   }

   core::Program::disusePrograms();
}

inline void Engine::initExtras() {
   /* FPS counter */
   mTextFPSCallback = NULL;

   /* Debugger */
   mDebugger = puDebugger (new Debugger(this));
   if(mIsDR) {
      #if __ANDROID__
      //   storeText("Normals", "bridgenorth", 0.50, 0.95, 50.0);
      //   storeText("Specular", "bridgenorth", 0.50, 0.50, 50.0);
      //   storeText("Color", "bridgenorth", 0.05, 0.95, 50.0);
      //   storeText("Position", "bridgenorth", 0.05, 0.50, 50.0);
      #else
      storeText("Normals", "fonts/bridgenorth", 0.50, 0.95, 50.0);
      storeText("Specular", "fonts/bridgenorth", 0.50, 0.50, 50.0);
      storeText("Color", "fonts/bridgenorth", 0.05, 0.95, 50.0);
      storeText("Position", "fonts/bridgenorth", 0.05, 0.50, 50.0);
      #endif
   }
}

inline void Engine::initPickingBuffer() {
   mPickingPixelBuffer = puPixelBuffer (new core::PixelBuffer(GL_STREAM_READ));
   reloadPickingBuffer();
}

inline void Engine::reloadGeometryBuffer() {
   mGBuffer->reload();
}

GLuint Engine::getFramesPassed() {
   GLuint result = mFrameCounter;
   mFrameCounter = 0;
   return result;
}

GLfloat Engine::getStartupAnimationTime() {
   return mStartupTimeLimit;
}

std::string Engine::getExecutablePath() {
   return mFileLoader.getRootPath();
}

void Engine::setCurrentScene(pScene scene) {
   if (scene) {
      if (mScene) {
         mScene->onHide();
      }
      mScene = scene;
      mScene->onShow();
   }
}

pScene Engine::getCurrentScene() {
   return mScene;
}

manager::LightManager* Engine::getLightManager() {
   return mLightManager.get();
}

puPhysicsMeshBuffer Engine::getPhysicalMeshBuffer(const std::string& shapePath) {
   PhysicsMeshBuffer* buffer = new PhysicsMeshBuffer();
   const fScene* scene = mImporter.ReadFile((getExecutablePath() + shapePath).c_str(),
         FILLWAVE_PROCESS_TRIANGULATE |
         FILLWAVE_PROCESS_SORT_BY_P_TYPE |
         FILLWAVE_PROCESS_CALC_TANGENT_SPACE);
   if (scene) {
      for (GLuint i = 0; i < scene->mNumMeshes; i++) {
         const fMesh* shape = scene->mMeshes[i];
         buffer->mNumFaces = shape->mNumFaces;
         buffer->mVertices.reserve(shape->mNumVertices);
         buffer->mIndices.reserve(shape->mNumFaces*3);
         for ( GLuint j = 0; j < shape->mNumFaces; j++) {
            buffer->mIndices.push_back(shape->mFaces[j].mIndices[0]);
            buffer->mIndices.push_back(shape->mFaces[j].mIndices[1]);
            buffer->mIndices.push_back(shape->mFaces[j].mIndices[2]);
         }
         for ( GLuint z = 0; z < shape->mNumVertices; z++) {
            glm::vec3 vertex(shape->mVertices[z].x, shape->mVertices[z].y, shape->mVertices[z].z);
            buffer->mVertices.push_back(vertex);
         }
         break;//for now fillwave supports only one mesh here;
      }
   }
   return puPhysicsMeshBuffer(buffer);
}

void Engine::addPostProcess(const std::string& fragmentShaderPath, GLfloat lifeTime) {
   pProgram program = mProgramLoader.getQuadCustomFragmentShader(this, fragmentShaderPath);
   common::PostProcessingPass pass(program,
                                   mWindowWidth,
                                   mWindowHeight,
                                   mTextureManager->getDynamic(fragmentShaderPath, program, glm::ivec2(mWindowWidth, mWindowHeight)),
                                   lifeTime);
   mPostProcessingPasses.push_back(pass);
   FLOG_DEBUG("Post processing pass added: %s", fragmentShaderPath.c_str());
}

void Engine::configureFPSCounter(std::string fontName,
                                 GLfloat xPosition,
                                 GLfloat yPosition,
                                 GLfloat size) {
   if (fontName.size() > 1) {
      mFPSText = storeText("",
                           fontName,
                           xPosition,
                           yPosition,
                           size);

      /* Provide callback to refresh the FPS value */
      mTextFPSCallback = new actions::FPSCallback(mFPSText);
      registerTimeCallback(mTextFPSCallback);
   } else {
      mFPSText.reset();
      unregisterTimeCallback(mTextFPSCallback);
   }
}

void Engine::configureFileLogging(std::string fileName) {
   if (fileName.size() > 1) {
      FLOG_INFO("File %s will be cleaned and used for logging.", fileName.c_str());
      setLogPath(fileName);
   } else {
      setFileInvalid();
      FLOG_INFO("File logging disabled.");
   }
}

inline void Engine::init() {
   initExtensions();

   initContext();

   initManagement();

   initPipelines();

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
   initStartup();
#endif
//   mFence = puFence(new core::Fence());
}

inline void Engine::initManagement() {
   mTextureManager = puTextureManager(new manager::TextureManager(mFileLoader.getRootPath()));

   mShaderManager = puShaderManager(new manager::ShaderManager(mFileLoader.getRootPath()));

   mProgramManager = puProgramManager(new manager::ProgramManager());

   mLightManager = puLightManager(new manager::LightManager(mWindowWidth, mWindowHeight));

   mSamplerManager = puSamplerManager(new manager::SamplerManager());

   mBufferManager = puBufferManager(new manager::BufferManager());
}

inline void Engine::initPipelines() {
   /* DR */
   mProgramDRDirecionalLight = mProgramLoader.getDRDirectionalLights(this);
   glm::vec2 screenSize(mWindowWidth, mWindowHeight);

   mProgramDRDirecionalLight->use();
   mProgramDRDirecionalLight->uniformPush("uWorldPositionAttachment", FILLWAVE_POSITION_ATTACHMENT);
   mProgramDRDirecionalLight->uniformPush("uDiffuseTexelAttachment", FILLWAVE_DIFFUSE_ATTACHMENT);
   mProgramDRDirecionalLight->uniformPush("uNormalAttachment", FILLWAVE_NORMAL_ATTACHMENT);
   mProgramDRDirecionalLight->uniformPush("uSpecularTexelAttachment", FILLWAVE_SPECULAR_ATTACHMENT);
   mProgramDRDirecionalLight->uniformPush("uScreenSize", screenSize);
   mProgramDRDirecionalLight->uniformPush("uAOMap", FILLWAVE_AO_UNIT);

   mProgramDRSpotLight = mProgramLoader.getDRSpotLights(this);

   mProgramDRSpotLight->use();
   mProgramDRSpotLight->uniformPush("uWorldPositionAttachment", FILLWAVE_POSITION_ATTACHMENT);
   mProgramDRSpotLight->uniformPush("uDiffuseTexelAttachment", FILLWAVE_DIFFUSE_ATTACHMENT);
   mProgramDRSpotLight->uniformPush("uNormalAttachment", FILLWAVE_NORMAL_ATTACHMENT);
   mProgramDRSpotLight->uniformPush("uSpecularTexelAttachment", FILLWAVE_SPECULAR_ATTACHMENT);
   mProgramDRSpotLight->uniformPush("uScreenSize", screenSize);
   mProgramDRSpotLight->uniformPush("uAOMap", FILLWAVE_AO_UNIT);

   mProgramDRPointLight = mProgramLoader.getDRPointLights(this);

   mProgramDRPointLight->use();
   mProgramDRPointLight->uniformPush("uWorldPositionAttachment", FILLWAVE_POSITION_ATTACHMENT);
   mProgramDRPointLight->uniformPush("uDiffuseTexelAttachment", FILLWAVE_DIFFUSE_ATTACHMENT);
   mProgramDRPointLight->uniformPush("uNormalAttachment", FILLWAVE_NORMAL_ATTACHMENT);
   mProgramDRPointLight->uniformPush("uSpecularTexelAttachment", FILLWAVE_SPECULAR_ATTACHMENT);
   mProgramDRPointLight->uniformPush("uScreenSize", screenSize);
   mProgramDRPointLight->uniformPush("uAOMap", FILLWAVE_AO_UNIT);

   mProgramDRDepthless = mProgramLoader.getDRDepthless(this);
   mProgramDRDepthless->use();
   mProgramDRDepthless->uniformPush("uWorldPositionAttachment", FILLWAVE_POSITION_ATTACHMENT);
   mProgramDRDepthless->uniformPush("uDiffuseTexelAttachment", FILLWAVE_DIFFUSE_ATTACHMENT);
   mProgramDRDepthless->uniformPush("uScreenSize", screenSize);

   mProgramDRAmbient = mProgramLoader.getDRAmbient(this);
   mProgramDRAmbient->use();
   mProgramDRAmbient->uniformPush("uDiffuseTexelAttachment", FILLWAVE_DIFFUSE_ATTACHMENT);
   mProgramDRAmbient->uniformPush("uScreenSize", screenSize);

   core::Program::disusePrograms();

   /* OT */
   mProgramOcclusionBox = mProgramLoader.getOcclusionOptimizedQuery(this);

   /* AO */
   mProgramAOGeometry = mProgramLoader.getAmbientOcclusionGeometry(this);
   mProgramAOColor = mProgramLoader.getAmbientOcclusionColor(this);

   /* Texture */
   mProgramTextureLookup = mProgramLoader.getQuad(this);

   mProgramTextureLookup->use();
   mProgramTextureLookup->uniformPush("uPostProcessingSampler", FILLWAVE_DIFFUSE_UNIT);
   core::Program::disusePrograms();
}

inline void Engine::initOcclusionTest() {
   std::vector<core::VertexPosition> vec = models::BoxOcclusion().getVertices();

   mVAOOcclusion = storeVAO();

   mVBOOcclusion = puVertexBufferPosition( new core::VertexBufferPosition(vec) );

   mVBOOcclusion->getAttributes(mProgramOcclusionBox->getHandle());

   mVBOOcclusion->attributesBind(mProgramOcclusionBox);

   mVAOOcclusion->bind();

   mVBOOcclusion->bind();

   mVBOOcclusion->attributesSetForVAO();

   mVBOOcclusion->send();

   mVAOOcclusion->unbind();
}

inline void Engine::initDeferredShading() {

   models::Material material;

   models::Sphere sphere(3.0f, 10.0f, 10.0f);
   std::vector<core::VertexBasic> vertices = sphere.getVertices();
   std::vector<GLuint> indices = sphere.getIndices();

   mDeferredPointLight = puMesh(new models::Mesh(this,
                                material,
                                buildTextureRegion(pTexture()),
                                buildTextureRegion(pTexture()),
                                buildTextureRegion(pTexture()),
                                mProgramDRPointLight,
                                pProgram(),
                                pProgram(),
                                mProgramOcclusionBox,
                                pProgram(),
                                pProgram(),
                                mLightManager.get(),
                                pVertexBufferBasic(new core::VertexBufferBasic(vertices)),
                                pIndexBufferBasic(new core::IndexBufferBasic(indices)),
                                nullptr));
}

inline void Engine::initAmbientOcclusion() {
   mAOGeometryBuffer = mTextureManager->getColor2D(mWindowWidth, mWindowHeight);
   mAOColorBuffer = mTextureManager->getColor2D(mWindowWidth, mWindowHeight);
}

inline void Engine::initGeometryBuffer() {
   GLint maxAttach = 0, maxDrawBuf = 0;
   glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxAttach);
   glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxDrawBuf);
   if (glm::max(maxAttach, maxDrawBuf) > mDeferredColorAttachments) {
//	   mIsDR = GL_TRUE;
	   mGBuffer = puFramebufferGeometry(new core::FramebufferGeometry(mTextureManager.get(), mWindowWidth, mWindowHeight, mDeferredColorAttachments, mDeferredDepthAttachments));
   }
}

inline void Engine::initUniformsCache() {
   mULCCameraPositionSpot = mProgramDRSpotLight->getUniformLocation("uCameraPosition");
   mULCAmbientIntensitySpot = mProgramDRSpotLight->getUniformLocation("uLight.base.ambientIntensity");
   mULCScreenSizeSpot = mProgramDRSpotLight->getUniformLocation("uScreenSize");
   mULCShadowUnitSpot = mProgramDRSpotLight->getUniformLocation("uShadowUnit");
   mULCIsAOSpot = mProgramDRSpotLight->getUniformLocation("uIsAO");

   mULCCameraPositionDirectional = mProgramDRDirecionalLight->getUniformLocation("uCameraPosition");
   mULCAmbientIntensityDirectional = mProgramDRDirecionalLight->getUniformLocation("uAmbientIntensity");
   mULCScreenSizeDirectional = mProgramDRDirecionalLight->getUniformLocation("uScreenSize");
   mULCShadowUnitDirectional = mProgramDRDirecionalLight->getUniformLocation("uShadowUnit");
   mULCIsAODirectional = mProgramDRDirecionalLight->getUniformLocation("uIsAO");

   mULCCameraPositionPoint = mProgramDRPointLight->getUniformLocation("uCameraPosition");
   mULCMVPPoint = mProgramDRPointLight->getUniformLocation("uMVP");
   mULCScreenSizePoint = mProgramDRPointLight->getUniformLocation("uScreenSize");
   mULCShadowUnitPoint = mProgramDRPointLight->getUniformLocation("uShadowUnit");
   mULCIsAOPoint = mProgramDRSpotLight->getUniformLocation("uIsAO");

   mULCDRDepthlesDiffuseTexel = mProgramDRDepthless->getUniformLocation("uDiffuseTexelAttachment");
   mULCDRDepthlessPositionTexel = mProgramDRDepthless->getUniformLocation("uWorldPositionAttachment");
   mULCDRScreenSize = mProgramDRDepthless->getUniformLocation("uScreenSize");

   uULCDRAScreenSize = mProgramDRAmbient->getUniformLocation("uScreenSize");
   uULCDRADiffuseAttachment = mProgramDRAmbient->getUniformLocation("uDiffuseTexelAttachment");
   uULCDRAAmbientGlobal = mProgramDRAmbient->getUniformLocation("uAmbient");
}

inline void Engine::initStartup() {

   pProgram program = mProgramLoader.getQuadCustomFragmentShaderStartup(this);

   program->use();
   program->uniformPush("uPostProcessingSampler", FILLWAVE_DIFFUSE_UNIT);
   program->uniformPush("uScreenFactor", static_cast<GLfloat>(mWindowWidth)/static_cast<GLfloat>(mWindowHeight));
   core::Program::disusePrograms();

   mPostProcessingPassStartup = puPostProcessingPass(
         new common::PostProcessingPass(program,
                                        mWindowWidth,
                                        mWindowHeight,
                                        mTextureManager->getDynamic("fillwave_quad_startup.frag", program, glm::ivec2(mWindowWidth, mWindowHeight)),
                                        mStartupTimeLimit) );

   FLOG_DEBUG("Post processing startup pass added");

   mStartupTexture = storeTexture("logo.png");
   if(not mStartupTexture) {
      mStartupTexture = storeTexture("textures/logo.png");
      if(not mStartupTexture) {
         mStartupTexture = storeTexture("64_64_64.color");
         FLOG_ERROR("Fillwave startup logo could not be executed");
      }
   }
}

pSampler Engine::storeSO(GLint textureUnit) {
   return mSamplerManager->get(textureUnit);
}

pVertexArray Engine::storeVAO(models::Reloadable* user) {
   return mBufferManager->getVAO(user);
}

void Engine::log() {
   FLOG_INFO("Fillwave engine");
   const GLubyte* renderer = glGetString (GL_RENDERER);
   const GLubyte* version = glGetString (GL_VERSION);
   FLOG_INFO("Renderer: %s\n", renderer);
   FLOG_INFO("OpenGL version supported %s\n", version);
}

void Engine::pick(GLuint x, GLuint y) {
   mPickingRenderableTexture->bindForRendering();

   drawClear();

   mScene->drawPicking();

   mPickingPixelBuffer->bind();

   glReadPixels(0, 0, mWindowWidth, mWindowHeight, GL_RGBA, GL_UNSIGNED_BYTE, 0);

   FLOG_CHECK("glReadPixels failed");
#ifdef __ANDROID__
   GLubyte* data = (GLubyte*)mPickingPixelBuffer->mapRange(GL_MAP_READ_BIT);
#else
   GLubyte* data = (GLubyte*)mPickingPixelBuffer->map(GL_READ_WRITE);
#endif

   glm::ivec4 colorRead = pickingBufferGetColor(data, x, y);
   mPickingPixelBuffer->unmap();
   mPickingPixelBuffer->unbind();
   core::Framebuffer::bindScreenFramebuffer();
   mScene->draw();
   mScene->pick(colorRead);
}

void Engine::captureFramebufferToFile(const std::string& name) {
   mPickingRenderableTexture->bindForRendering();
   drawClear();
   mScene->draw();
   mPickingPixelBuffer->bind();
   glReadPixels(0, 0, mWindowWidth, mWindowHeight, GL_RGBA, GL_UNSIGNED_BYTE, 0);
   FLOG_CHECK("reading pixel buffer failed");
#ifdef __ANDROID__
   GLubyte* data = (GLubyte*)mPickingPixelBuffer->mapRange(GL_MAP_READ_BIT);
#else
   GLubyte* data = (GLubyte*)mPickingPixelBuffer->map(GL_READ_WRITE);
#endif
   data[mWindowWidth*mWindowHeight*4]='\0';
   FILE* file;
   file = fopen(mFileLoader.getRootPath(name).c_str(), "w");
   if (file == nullptr) {
      FLOG_ERROR("Error when takin' screenshot");
      exit(1);
   }
   for(GLuint i=0; i<mWindowWidth*mWindowHeight; i++) {
      fprintf(file,"%c",data[4*i]);
      fprintf(file,"%c",data[4*i+1]);
      fprintf(file,"%c",data[4*i+2]);
      fprintf(file,"%c",data[4*i]+3);
   }
   fclose(file);
   mPickingPixelBuffer->unmap();
   mPickingPixelBuffer->unbind();
   core::Framebuffer::bindScreenFramebuffer();
   mScene->draw();
}

void Engine::captureFramebufferToBuffer(GLubyte* buffer,
                                        GLint* sizeInBytes,
                                        GLuint format,
                                        GLint bytesPerPixel) {
   mPickingRenderableTexture->bindForRendering();
   drawClear();
   mScene->draw();
   mPickingPixelBuffer->bind();
   glReadPixels(0, 0, mWindowWidth, mWindowHeight, format, GL_UNSIGNED_BYTE, 0);
   FLOG_CHECK("reading pixel buffer failed");
#ifdef __ANDROID__
   buffer = (GLubyte*)mPickingPixelBuffer->mapRange(GL_MAP_READ_BIT);
#else
   buffer = (GLubyte*)mPickingPixelBuffer->map(GL_READ_WRITE);
#endif
   buffer[mWindowWidth*mWindowHeight*bytesPerPixel]='\0';
   *sizeInBytes = mWindowWidth*mWindowHeight*bytesPerPixel;
}

void Engine::reload() {

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

inline void Engine::reloadPickingBuffer() {
   mPickingRenderableTexture = mTextureManager->getColor2D(mWindowWidth, mWindowHeight);

   mPickingPixelBuffer->setScreenSize(mWindowWidth, mWindowHeight, 4);
   mPickingPixelBuffer->bind();
   mPickingPixelBuffer->setReady();
   mPickingPixelBuffer->send();
   glReadPixels(0, 0, mWindowWidth, mWindowHeight, GL_RGBA, GL_UNSIGNED_BYTE, 0);
   FLOG_CHECK("glReadPixels");
   mPickingPixelBuffer->unbind();
}

inline void Engine::initContext( void ) {
   glClearColor(mBackgroundColor.x, mBackgroundColor.y, mBackgroundColor.z, 1.0f);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   FLOG_CHECK("Could not set OpenGL depth testing options");
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);
   glFrontFace(GL_CCW);
   FLOG_CHECK("Could not set OpenGL culling options");
}

const fScene* Engine::getModelFromFile(std::string path) {
   FLOG_DEBUG("Reading model %s", path.c_str());
#ifdef FILLWAVE_COMPILATION_TINY_ASSET_LOADER
   return nullptr;
#else
   return mImporter.ReadFile((getExecutablePath() + path).c_str(),
         aiProcess_Triangulate | aiProcess_SortByPType | aiProcess_CalcTangentSpace);
#endif
}

GLboolean Engine::isDR () {
  return mIsDR;
}

#ifndef __ANDROID__

pShader Engine::storeShaderGeometry(const std::string& shaderPath) {
   return mShaderManager->add(shaderPath, GL_GEOMETRY_SHADER);}

pShader Engine::storeShaderGeometry(const std::string& shaderPath, const std::string& shaderSource) {
   return mShaderManager->add(shaderPath, GL_GEOMETRY_SHADER, shaderSource);}

pShader Engine::storeShaderTesselationControl(const std::string& shaderPath) {
   return mShaderManager->add(shaderPath, GL_TESS_CONTROL_SHADER);
}

pShader Engine::storeShaderTesselationControl(const std::string& shaderPath, const std::string& shaderSource) {
   return mShaderManager->add(shaderPath, GL_TESS_CONTROL_SHADER, shaderSource);
}

pShader Engine::storeShaderTesselationEvaluation(const std::string& shaderPath) {
   return mShaderManager->add(shaderPath, GL_TESS_EVALUATION_SHADER);
}

pShader Engine::storeShaderTesselationEvaluation(const std::string& shaderPath, const std::string& shaderSource) {
   return mShaderManager->add(shaderPath, GL_TESS_EVALUATION_SHADER, shaderSource);
}

inline void Engine::initExtensions( void ) {
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

inline void Engine::initGeometryShading() {
   GLint MaxPatchVertices = 0;
   glGetIntegerv(GL_MAX_PATCH_VERTICES, &MaxPatchVertices);
   FLOG_DEBUG("Max supported patch vertices %d\n", MaxPatchVertices);
   glPatchParameteri(GL_PATCH_VERTICES, 3);
}

#else
inline void Engine::initExtensions() {
   glesInitExtensions();
}

#endif

} /* fillwave */
