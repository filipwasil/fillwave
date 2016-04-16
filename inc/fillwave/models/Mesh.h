/*
 * Mesh.h
 *
 *  Created on: Feb 19, 2014
 *      Author: Filip Wasil
 */

#ifndef MESH_H_
#define MESH_H_

#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/core/buffers/IndexBuffer.h>
#include <fillwave/core/buffers/VertexBufferBasic.h>
#include <fillwave/core/operations/ConditionalRender.h>
#include <fillwave/core/operations/TQuery.h>
#include <fillwave/models/Entity.h>
#include <fillwave/models/base/Material.h>
#include <fillwave/core/pipeline/Fence.h>
#include <fillwave/models/base/IReloadable.h>
#include <fillwave/renderers/IRenderer.h>

namespace fillwave {
class Engine;

namespace framework {
class Animator;
class LightSystem;
}

namespace framework {

/*! \class Mesh
 * \brief Basic drawable Entity.
 */
class Mesh: public Entity, public IReloadable {
 public:
	Mesh(
	   Engine* engine,
	   const Material& material,
	   core::Texture2D* diffuseMap,
	   core::Texture2D* normalMap,
	   core::Texture2D* specularMap,
	   core::Program* program,
	   core::Program* ProgramShadow,
	   core::Program* programShadowColor,
	   core::Program* programOcclusion,
	   core::Program* programAmbientOcclusionGeometry,
	   core::Program* programAmbientOcclusionColor,
	   LightSystem* lights = nullptr,
	   core::VertexBufferBasic* vbo = nullptr,
	   core::IndexBuffer* ibo = nullptr,
	   Animator* animator = nullptr,
	   GLenum renderMode = GL_TRIANGLES,
	   core::VertexArray* vao = nullptr);

	virtual ~Mesh() = default;

	/* IDrawable */
	void draw(ICamera& camera) override;
	void drawPBRP(ICamera& camera) override;
	void drawDR(ICamera& camera) override;
	void drawPicking(ICamera& camera) override;
	void drawDepth(ICamera& camera) override;
	void drawDepthColor(ICamera& camera, glm::vec3& position) override;
	void drawAOG(ICamera& camera) override;
	void drawAOC(ICamera& camera) override;
	void drawOcclusionBox(ICamera& camera) override;

	/* IRenderable */
	virtual void updateRenderer(IRenderer& renderer) override;
	virtual bool getRenderItem(RenderItem& item) override;

	void log() const;

	void drawFast(ICamera& camera);
	virtual void onDraw();

 protected:
	Material mMaterial;
	core::Texture2D *mDiffuseMap, *mNormalMap, *mSpecularMap;
	core::Program *mProgram, *mProgramShadow, *mProgramShadowColor, *mProgramOQ,
	     *mProgramAOGeometry, *mProgramAOColor;
	GLenum mRenderMode;

	/* Buffers */
	core::IndexBuffer* mIBO;
	core::VertexBufferBasic* mVBO;

	/* Light */
	LightSystem* mLights;

	/* Animations */
	Animator* mAnimator;

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
