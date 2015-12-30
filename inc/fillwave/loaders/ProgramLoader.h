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

class ProgramLoader : public ShaderLoader {
public:
	ProgramLoader() = default;

	virtual ~ProgramLoader() = default;

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
	pProgram getQuadCustomFragmentShader(
			Engine* engine,
			const std::string& shaderPath);

	static void initDefaultUniforms(core::Program* program);
private:

	const char *mFeedbackVaryingsGPUEmiter[6];

	pProgram getDefaultDR(Engine* engine);
	pProgram getDefaultFR(Engine* engine);
	pProgram getDefaultBonesDR(Engine* engine);
	pProgram getDefaultBonesFR(Engine* engine);

};

} /* framework */
} /* fillwave */

#endif /* SRC_LOADERS_PROGRAMLOADER_H_ */
