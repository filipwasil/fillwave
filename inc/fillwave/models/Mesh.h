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
#include <fillwave/models/Material.h>
#include <fillwave/core/pipeline/Fence.h>
#include <fillwave/models/Reloadable.h>

namespace fillwave {
class Engine;

namespace manager {
class BoneManager;
class LightManager;
}

namespace models {

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
			manager::LightManager* lightManager = nullptr,
			pVertexBufferBasic vbo = pVertexBufferBasic(),
			pIndexBufferBasic ibo = pIndexBufferBasic(),
			manager::BoneManager* boneManager = nullptr,
			GLenum drawType = GL_TRIANGLES);

	virtual ~Mesh() = default;

	virtual void onDraw();

	void draw(space::Camera& camera);

	void drawDR(space::Camera& camera);

	void drawFast(space::Camera& camera);

	void drawPicking(space::Camera& camera);

	void drawDepth(space::Camera& camera);

	void drawDepthColor(space::Camera& camera, glm::vec3& position);

	void drawAOG(space::Camera& camera);

	void drawAOC(space::Camera& camera);

	void drawOcclusionBox(space::Camera& camera);

	void log();

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
	manager::LightManager* mLightManager;

	/* Animations */
	manager::BoneManager* mBoneManager;

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

} /* models */
typedef std::shared_ptr<models::Mesh> pMesh;
typedef std::unique_ptr<models::Mesh> puMesh;
} /* fillwave */

#endif /* MODELOBJ_H_ */
