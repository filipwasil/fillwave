/*
 * Mesh.h
 *
 *  Created on: Feb 19, 2014
 *      Author: Filip Wasil
 */

#ifndef MESH_H_
#define MESH_H_

#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/core/texturing/TextureRegion.h>
#include <fillwave/core/buffers/VertexBufferBasic.h>
#include <fillwave/core/buffers/IndexBufferBasic.h>
#include <fillwave/core/operations/Query.h>
#include <fillwave/core/operations/ConditionalRender.h>
#include <fillwave/models/Entity.h>
#include <fillwave/models/base/Material.h>
#include <fillwave/models/base/Reloadable.h>
#include <fillwave/core/pipeline/Fence.h>

namespace fillwave {
class Engine;

namespace framework {
class Animator;
class LightManager;
}

namespace framework {

/*! \class Mesh
 * \brief Basic drawable Entity.
 */

class Mesh: public Entity, public Reloadable {
public:
	Mesh(
			Engine* engine,
			const Material& material,
			pTextureRegion diffuseMap,
			pTextureRegion normalMap,
			pTextureRegion specularMap,
			pProgram program,
			pProgram ProgramShadow,
			pProgram programShadowColor,
			pProgram programOcclusion,
			pProgram programAmbientOcclusionGeometry,
			pProgram programAmbientOcclusionColor,
			LightManager* lightManager = nullptr,
			pVertexBufferBasic vbo = pVertexBufferBasic(),
			pIndexBufferBasic ibo = pIndexBufferBasic(),
			Animator* boneManager = nullptr,
			GLenum drawType = GL_TRIANGLES);

	virtual ~Mesh() = default;

   void updateRenderpass(std::map<GLuint, std::vector<Entity*> >& renderpasses);

	void draw(ICamera& camera);
	void drawPBRP(ICamera& camera);
	void drawDR(ICamera& camera);
	void drawFast(ICamera& camera);
	void drawPicking(ICamera& camera);
	void drawDepth(ICamera& camera);
	void drawDepthColor(ICamera& camera, glm::vec3& position);
	void drawAOG(ICamera& camera);
	void drawAOC(ICamera& camera);
	void drawOcclusionBox(ICamera& camera);
	void log() const;

	virtual void onDraw();

protected:
	Material mMaterial;
	pTextureRegion mDiffuseMap;
	pTextureRegion mNormalMap;
	pTextureRegion mSpecularMap;
	pProgram mProgram, mProgramDR, mProgramShadow, mProgramShadowColor,
			mProgramOQ, mProgramAOGeometry, mProgramAOColor;

	/* Buffers */
	pIndexBufferBasic mIBO;
	pVertexBufferBasic mVBO;

	/* Light */
	LightManager* mLightManager;

	/* Animations */
	Animator* mAnimator;

	/* Draw */
	GLenum mDrawType;

	/* Occlusion cut off */
	glm::mat4 mOcclusionMatrix;
	core::QueryIfAnySamplesPassed mOcclusionQuery;
//   puFence mFence;

#ifdef FILLWAVE_GLES_3_0
#else
//   core::QueryTimeElapsed mTimeQuery;
	core::ConditionalRender mConditionalRendering;
#endif

private:

	/* ULC - Uniform location cache */
	GLint mULCModelMatrix, mULCViewProjectionMatrix, mULCLightAmbientIntensity,
			mULCLightDiffuseIntensity, mULCLightSpecularIntensity,
			mULCCameraPosition, mULCColorPicking, mULCPainterColor;
	GLint mULCMVPOcclusion;
	GLint mULCMVPShadow;
	GLint mULCMVPShadowColor, mULCModelMatrixShadowColor;
	GLint mULCMVPAmbientOcclusion, mULCPositionAmbientOcclusion;
	GLint mULCSampleRadius, mULCProjectionMatrix;

	void initBuffers();
	void initPipeline();
	void initUniformsCache();
	void initVAO();
	void initVBO();
	void bindTextures();
	void coreDraw();
};

} /* framework */
typedef std::shared_ptr<framework::Mesh> pMesh;
typedef std::unique_ptr<framework::Mesh> puMesh;
} /* fillwave */

#endif /* MODELOBJ_H_ */
