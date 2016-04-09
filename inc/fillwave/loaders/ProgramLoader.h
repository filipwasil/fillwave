/*
 * ProgramLoader.h
 *
 *  Created on: May 4, 2015
 *      Author: Filip Wasil
 */

#ifndef SRC_LOADERS_PROGRAMLOADER_H_
#define SRC_LOADERS_PROGRAMLOADER_H_

#include <fillwave/core/pipeline/Program.h>
#include <fillwave/loaders/ShaderLoader.h>

namespace fillwave {
class Engine;
namespace framework {

/*! \class ProgramLoader
 * \brief Loads programs.
 */

class ProgramLoader: public ShaderLoader {
 public:
	ProgramLoader(Engine* engine);

	virtual ~ProgramLoader() = default;

	core::Program* getDefault();
	core::Program* getDefaultBones();
	core::Program* getDefaultDR();
	core::Program* getDefaultFR();
	core::Program* getDefaultBonesDR();
	core::Program* getDefaultBonesFR();
	core::Program* getShadow();
	core::Program* getShadowColorCoded();
	core::Program* getShadowWithAnimation();
	core::Program* getShadowColorCodedWithAnimation();
	core::Program* getDebugger();
	core::Program* getSkybox();
	core::Program* getSkyboxDR();
	core::Program* getHUD();
	core::Program* getText();
	core::Program* getTextBold();
	core::Program* getParticleGPUEmiter();
	core::Program* getParticleGPU();
	core::Program* getParticleCPU();
	core::Program* getParticleCPUNoDepthText();
	core::Program* getQuad();
	core::Program* getQuadCustomFragmentShaderStartup();
	core::Program* getCursor();
	core::Program* getDRAmbient();
	core::Program* getAmbientOcclusionGeometry();
	core::Program* getAmbientOcclusionColor();
	core::Program* getOcclusionPureQuery();
	core::Program* getOcclusionQuery();
	core::Program* getOcclusionOptimizedQuery();
	core::Program* getDRDepthless();
	core::Program* getDRDirectionalLights();
	core::Program* getDRSpotLights();
	core::Program* getDRPointLights();
	core::Program* getQuadCustomFragmentShader(const std::string& shaderPath);
	core::Program* getHUDCustomFragmentShader(const std::string& shaderPath);

	static void initDefaultUniforms(core::Program* program);
 private:

	Engine* mEngine;

	const char *mFeedbackVaryingsGPUEmiter[6];
};

} /* framework */
} /* fillwave */

#endif /* SRC_LOADERS_PROGRAMLOADER_H_ */
