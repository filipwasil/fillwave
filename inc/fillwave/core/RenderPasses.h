/*
 * RenderPasses.h
 *
 *  Created on: Dec 20, 2015
 *      Author: filip
 */

#ifndef INC_FILLWAVE_CORE_RENDERPASSES_H_
#define INC_FILLWAVE_CORE_RENDERPASSES_H_

/*! \class Scene
 * \brief Entity to be a root of Entity tree.
 */

enum class eRenderPass {
	eEmpty, // default for entity
	eDefault, // getDefault(Engine* engine);
	eDefaultAnimated, // getDefaultBones(Engine* engine);
	eShadow, // getShadow(Engine* engine);
	eShadowAnimated, // getShadowWithAnimation(Engine* engine);
	eShadowColorCoded, // getShadowColorCoded(Engine* engine);
	eShadowColorCodedAnimated, // getShadowColorCodedWithAnimation(Engine* engine);
	eSkybox, // getSkybox(Engine* engine);
	eSkyboxDR, // getSkyboxDR(Engine* engine);
	eText, // getText(Engine* engine);
	eTextBold, // getTextBold(Engine* engine);
	eParticleGPUEmiter, // pProgram getParticleGPUEmiter(Engine* engine);
	eParticleGPU, // getParticleGPU(Engine* engine);
	eParticleCPU, // getParticleCPU(Engine* engine);
	eParticleCPUNoDepthTest, // getParticleCPUNoDepthText(Engine* engine);
	eQuad, // getQuad(Engine* engine);
	eStartup, // getQuadCustomFragmentShaderStartup(Engine* engine);
	eCursor, // getCursor(Engine* engine);
	eAmbientDR, // getDRAmbient(Engine* engine);
	eAOGeometry, // getAmbientOcclusionGeometry(Engine* engine);
	eAOColor, // getAmbientOcclusionColor(Engine* engine);
	eOQPure, // getOcclusionPureQuery(Engine* engine);
	eOQ, // getOcclusionQuery(Engine* engine);
	eOQOptimized, //getOcclusionOptimizedQuery(Engine* engine);
	eDepthlessDR, // getDRDepthless(Engine* engine);
	eDirectionalLightDR, // getDRDirectionalLights(Engine* engine);
	eSpotLightDR, // getDRSpotLights(Engine* engine);
	ePointLightDR, // getDRPointLights(Engine* engine);
	//	pProgram getDebugger(Engine* engine);
};


#endif /* INC_FILLWAVE_CORE_RENDERPASSES_H_ */
