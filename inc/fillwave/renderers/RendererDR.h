/*
 * RendererDR.h
 *
 *  Created on: Jan 5, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_RENDERERS_RENDERERDR_H_
#define INC_FILLWAVE_RENDERERS_RENDERERDR_H_

#include <fillwave/renderers/IRenderer.h>
#include <fillwave/core/rendering/FramebufferGeometry.h>
#include <fillwave/models/Mesh.h>
#include <fillwave/Math.h>

#if defined(FILLWAVE_GLES_3_0)
#else

namespace fillwave {
namespace framework {

class ProgramLoader;

/*! \class RendererDR
 * \brief Deferred IRenderer. Not ready (Rev.4.2.1).
 */

class RendererDR: public IRenderer {
public:
	RendererDR(Engine* engine, ProgramLoader& loader);
	virtual ~RendererDR() = default;

	void update(IRenderable* renderable) override;
	void draw(ICamera& camera) override;
	void reset(GLuint width, GLuint height) override;
	void clear() override;

	/* Init */
	void initGeometryBuffer();
	void initGeometryShading();
	void initUniforms();
	void initUniformsCache();

	/* Passes */
	void drawSceneCoreDR();
	void drawGeometryPass(ICamera& camera);
	void drawDepthlessPass();
	void drawAmbientPass();
	void drawAOPass(ICamera& camera);
	void drawColorPass(ICamera& camera);
	void drawLightsSpotPass(ICamera& camera, GLint& textureUnit);
	void drawLightsDirectionalPass(ICamera& camera, GLint& textureUnit);
	void drawLightsPointPass(ICamera& camera, GLint& textureUnit);
	void drawColorPassBegin();
	void drawColorPassEnd();
	void drawDebug();

private:
	glm::vec2 mScreenSize;

	LightSystem* mLights;
	TextureSystem* mTextures;

	pProgram mProgramMain, mProgramMainAnimated, mProgramDirecionalLight,
			mProgramSpotLight, mProgramPointLight, mProgramDepthless,
			mProgramAmbient, mProgramAOGeometry, mProgramAOColor;

	pTexture2DRenderable mAOGeometryBuffer;
	pTexture2DRenderable mAOColorBuffer;

	puMesh mDeferredPointLight;

	GLint mULCDRDepthlesDiffuseTexel, mULCDRDepthlessPositionTexel,
			mULCDRScreenSize, mULCDRAScreenSize, mULCDRADiffuseAttachment,
			mULCAmbient;

	GLint mULCCameraPositionDirectional, mULCAmbientIntensityDirectional,
			mULCScreenSizeDirectional, mULCShadowUnitDirectional,
			mULCIsAODirectional, mULCCameraPositionPoint,
			mULCAmbientIntensityPoint, mULCMVPPoint, mULCScreenSizePoint,
			mULCShadowUnitPoint, mULCIsAOPoint;

	/* ULC - Uniform location cache */
	GLint mULCCameraPositionSpot, mULCAmbientIntensitySpot, mULCScreenSizeSpot,
			mULCShadowUnitSpot, mULCIsAOSpot;

	GLboolean mIsAO;

	const GLuint mDeferredColorAttachments;
	const GLuint mDeferredDepthAttachments;

	puFramebufferGeometry mGBuffer;

	std::vector<IRenderable*> mNodes; /* true -> animated, false -> not animated */
	std::vector<IRenderable*> mAnimatedNodes; /* true -> animated, false -> not animated */
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* defined(FILLWAVE_GLES_3_0) */
#endif /* INC_FILLWAVE_RENDERERS_RENDERERDR_H_ */
