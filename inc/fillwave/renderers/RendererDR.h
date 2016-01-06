/*
 * RendererDR.h
 *
 *  Created on: Jan 5, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_RENDERERS_RENDERERDR_H_
#define INC_FILLWAVE_RENDERERS_RENDERERDR_H_

#if defined(FILLWAVE_GLES_3_0)
#else

#include <fillwave/renderers/IRenderer.h>
#include <fillwave/core/rendering/FramebufferGeometry.h>
#include <fillwave/models/Mesh.h>
#include <fillwave/Math.h>

namespace fillwave {
namespace framework {

class ProgramLoader;

class RendererDR: public IRenderer {
public:
	RendererDR(Engine* engine, ProgramLoader& loader);
	virtual ~RendererDR() = default;

	void onScreenResize(GLuint width, GLuint height);
	void update(GLuint* programId, Entity* entity);
	void draw(ICamera& camera);
	void reset();

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

	LightManager* mLightManager;
	TextureManager* mTextureManager;

	pProgram mProgramMain, mProgramMainAnimated, mProgramDirecionalLight, mProgramSpotLight,
			mProgramPointLight, mProgramDepthless, mProgramAmbient,
			mProgramAOGeometry, mProgramAOColor;

	pTexture2DRenderable mAOGeometryBuffer;
	pTexture2DRenderable mAOColorBuffer;

	puMesh mDeferredPointLight;

	GLint mULCDRDepthlesDiffuseTexel, mULCDRDepthlessPositionTexel,
			mULCDRScreenSize, mULCDRAScreenSize, mULCDRADiffuseAttachment, mULCAmbient;

	GLint mULCCameraPositionDirectional, mULCAmbientIntensityDirectional,
			mULCScreenSizeDirectional, mULCShadowUnitDirectional,
			mULCIsAODirectional, mULCCameraPositionPoint, mULCAmbientIntensityPoint, mULCMVPPoint,
			mULCScreenSizePoint, mULCShadowUnitPoint, mULCIsAOPoint;

	/* ULC - Uniform location cache */
	GLint mULCCameraPositionSpot, mULCAmbientIntensitySpot, mULCScreenSizeSpot,
			mULCShadowUnitSpot, mULCIsAOSpot;

	GLboolean mIsAO;

	const GLuint mDeferredColorAttachments;
	const GLuint mDeferredDepthAttachments;

	puFramebufferGeometry mGBuffer;

	std::vector<Entity*> mNodes; /* true -> animated, false -> not animated */
	std::vector<Entity*> mAnimatedNodes; /* true -> animated, false -> not animated */
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* defined(FILLWAVE_GLES_3_0) */
#endif /* INC_FILLWAVE_RENDERERS_RENDERERDR_H_ */
