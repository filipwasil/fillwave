/*
 * ProgramLoader.h
 *
 *  Created on: May 4, 2015
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
