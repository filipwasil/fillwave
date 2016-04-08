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

	pProgram getDefault();
	pProgram getDefaultBones();
	pProgram getDefaultDR();
	pProgram getDefaultFR();
	pProgram getDefaultBonesDR();
	pProgram getDefaultBonesFR();
	pProgram getShadow();
	pProgram getShadowColorCoded();
	pProgram getShadowWithAnimation();
	pProgram getShadowColorCodedWithAnimation();
	pProgram getDebugger();
	pProgram getSkybox();
	pProgram getSkyboxDR();
	pProgram getHUD();
	pProgram getText();
	pProgram getTextBold();
	pProgram getParticleGPUEmiter();
	pProgram getParticleGPU();
	pProgram getParticleCPU();
	pProgram getParticleCPUNoDepthText();
	pProgram getQuad();
	pProgram getQuadCustomFragmentShaderStartup();
	pProgram getCursor();
	pProgram getDRAmbient();
	pProgram getAmbientOcclusionGeometry();
	pProgram getAmbientOcclusionColor();
	pProgram getOcclusionPureQuery();
	pProgram getOcclusionQuery();
	pProgram getOcclusionOptimizedQuery();
	pProgram getDRDepthless();
	pProgram getDRDirectionalLights();
	pProgram getDRSpotLights();
	pProgram getDRPointLights();
	pProgram getQuadCustomFragmentShader(const std::string& shaderPath);
	pProgram getHUDCustomFragmentShader(const std::string& shaderPath);

	static void initDefaultUniforms(core::Program* program);
private:

	Engine* mEngine;

	const char *mFeedbackVaryingsGPUEmiter[6];
};

} /* framework */
} /* fillwave */

#endif /* SRC_LOADERS_PROGRAMLOADER_H_ */
