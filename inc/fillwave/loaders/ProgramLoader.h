/*
 * ProgramLoader.h
 *
 *  Created on: May 4, 2015
 *      Author: Filip Wasil
 */

#ifndef SRC_LOADERS_PROGRAMLOADER_H_
#define SRC_LOADERS_PROGRAMLOADER_H_

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

#include <fillwave/core/pipeline/Program.h>

namespace fillwave {
class Engine;
namespace loader {

/*! \class ProgramLoader
 * \brief Loads programs.
 */

class ProgramLoader {
public:
   ProgramLoader();

   virtual ~ProgramLoader();

   pProgram getShadow(Engine* engine);

   pProgram getShadowColorCoded(Engine* engine);

   pProgram getShadowWithAnimation(Engine* engine);

   pProgram getShadowColorCodedWithAnimation(Engine* engine);

   pProgram getDebugger(Engine* engine);

   pProgram getSkybox(Engine* engine);

   pProgram getSkyboxDR(Engine* engine);

   pProgram getText(Engine* engine);

   pProgram getTextBold(Engine* engine);

   pProgram getParticleGPUEmiter(Engine* engine);

   pProgram getParticleGPU(Engine* engine);

   pProgram getParticleCPU(Engine* engine);

   pProgram getParticleCPUNoDepthText(Engine* engine);

   pProgram getQuad(Engine* engine);

   pProgram getQuadCustomFragmentShader(Engine* engine, const std::string& shaderPath);

   pProgram getQuadCustomFragmentShaderStartup(Engine* engine);

   pProgram getCursor(Engine* engine);

   pProgram getDRAmbient(Engine* engine);

   pProgram getAmbientOcclusionGeometry(Engine* engine);

   pProgram getAmbientOcclusionColor(Engine* engine);

   pProgram getOcclusionPureQuery(Engine* engine);

   pProgram getOcclusionQuery(Engine* engine);

   pProgram getOcclusionOptimizedQuery(Engine* engine);

   pProgram getDefault(Engine* engine);

   pProgram getDefaultBones(Engine* engine);

   pProgram getDRDepthless(Engine* engine);

   pProgram getDRDirectionalLights(Engine* engine);

   pProgram getDRSpotLights(Engine* engine);

   pProgram getDRPointLights(Engine* engine);

   static void initDefaultUniforms(core::Program* program);
private:
   GLuint mGeneratedProgramIndex;

   const char *mFeedbackVaryingsGPUEmiter[6];

   pProgram getDefaultDR(Engine* engine);

   pProgram getDefaultFR(Engine* engine);

   pProgram getDefaultBonesDR(Engine* engine);

   pProgram getDefaultBonesFR(Engine* engine);

};

} /* core */
} /* fillwave */

#endif /* SRC_LOADERS_PROGRAMLOADER_H_ */
