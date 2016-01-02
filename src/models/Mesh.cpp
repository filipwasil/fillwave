/*
 * Fillwave
 *
 */

#include <fillwave/models/Mesh.h>

#include <fillwave/management/LightManager.h>
#include <fillwave/models/animations/Animator.h>

#include <fillwave/loaders/ProgramLoader.h>

#include <fillwave/common/string.h>

#include <fillwave/Profiler.h>

FLOGINIT("Mesh", FERROR | FFATAL | FINFO)

using namespace std;

namespace fillwave {
namespace framework {

const GLint gOQVertices = 36;

Mesh::Mesh(
		Engine* engine,
		const Material& material,
		pTextureRegion diffuseMap,
		pTextureRegion normalMap,
		pTextureRegion specularMap,
		pProgram program,
		pProgram programShadow,
		pProgram programShadowColor,
		pProgram programOcclusion,
		pProgram programAmbientOcclusionGeometry,
		pProgram programAmbientOcclusionColor,
		LightManager* lightManager,
		pVertexBufferBasic vbo,
		pIndexBufferBasic ibo,
		Animator* boneManager,
		GLenum drawType)
		:
				Reloadable(engine),
				mMaterial(material),
				mDiffuseMap(diffuseMap),
				mNormalMap(normalMap),
				mSpecularMap(specularMap),
				mProgram(program),
				mProgramShadow(programShadow),
				mProgramShadowColor(programShadowColor),
				mProgramOQ(programOcclusion),
				mProgramAOGeometry(programAmbientOcclusionGeometry),
				mProgramAOColor(programAmbientOcclusionColor),
				mIBO(ibo),
				mVBO(vbo),
				mLightManager(lightManager),
				mAnimator(boneManager),
				mDrawType(drawType)
#ifdef FILLWAVE_GLES_3_0
#else
						,
				mConditionalRendering(GL_QUERY_WAIT)
#endif
{
	initPipeline();
	initVBO();
	initVAO();
	initUniformsCache();
}

void Mesh::drawPBRP(ICamera& camera) {
#ifdef FILLWAVE_GLES_3_0
#else
	if (mAnimator || mOcclusionQuery.getResultAsync(1))
#endif
	{
		core::Uniform::push(mULCModelMatrix, mPhysicsMMC);
		core::Uniform::push(mULCLightAmbientIntensity, mMaterial.getAmbient());
		core::Uniform::push(mULCLightDiffuseIntensity, mMaterial.getDiffuse());
		core::Uniform::push(mULCLightSpecularIntensity,
				mMaterial.getSpecular());
		core::Uniform::push(mULCCameraPosition, camera.getTranslation());
		core::Uniform::push(mULCViewProjectionMatrix,
				camera.getViewProjection());

		coreDraw();
	}
}

void Mesh::draw(ICamera& camera) {
#ifdef FILLWAVE_GLES_3_0
#else
	if (mAnimator || mOcclusionQuery.getResultAsync(1))
#endif
	{
		mProgram->use();

		core::Uniform::push(mULCModelMatrix, mPhysicsMMC);
		core::Uniform::push(mULCLightAmbientIntensity, mMaterial.getAmbient());
		core::Uniform::push(mULCLightDiffuseIntensity, mMaterial.getDiffuse());
		core::Uniform::push(mULCLightSpecularIntensity,
				mMaterial.getSpecular());
		core::Uniform::push(mULCCameraPosition, camera.getTranslation());
		core::Uniform::push(mULCViewProjectionMatrix,
				camera.getViewProjection());

		mLightManager->pushLightUniforms(mProgram.get());

		coreDraw();
	}
}

void Mesh::drawDR(ICamera& camera) {
#ifdef FILLWAVE_GLES_3_0
#else
	if (mAnimator || mOcclusionQuery.getResultAsync(1))
#endif
	{
		mProgram->use();

		core::Uniform::push(mULCModelMatrix, mPhysicsMMC);
		core::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());

		//   core::Uniform::push(mULCLightAmbientIntensity, mMaterial.getAmbient());
		//   core::Uniform::push(mULCLightDiffuseIntensity, mMaterial.getDiffuse());
		//   core::Uniform::push(mULCLightSpecularIntensity, mMaterial.getSpecular());
		//   core::Uniform::push(mULCCameraPosition, camera.getTranslation());

//      mLightManager->pushLightUniformsShadowMaps(mProgram.get());

		mLightManager->pushLightUniformsDR();

		coreDraw();
	}
}

void Mesh::drawFast(ICamera&) {
	mProgram->use();
	coreDraw();
}

inline void Mesh::coreDraw() {
	mVAO->bind();

	mLightManager->bindShadowmaps();

	bindTextures();

	//xxx blinking scene
	//xxx (OpenGL 3.3+)consider using conditional rendering this way:
	//#ifdef FILLWAVE_GLES_3_0
	//#else
	//   mConditionalRendering.begin(mOcclusionQuery.getID());
	onDraw();
	//   mConditionalRendering.end();
	//
	//#endif

	mVAO->unbind();

	core::Texture2D::unbind2DTextures();

	core::Program::disusePrograms();
}

inline void Mesh::bindTextures() {
	if (mDiffuseMap->getTexture()) {
		mDiffuseMap->getTexture()->bind(FILLWAVE_DIFFUSE_UNIT); //xxx texture region coordinates are not used
	}

	if (mNormalMap->getTexture()) {
		mNormalMap->getTexture()->bind(FILLWAVE_NORMAL_UNIT); //xxx texture region coordinates are not used
	}

	if (mSpecularMap->getTexture()) {
		mSpecularMap->getTexture()->bind(FILLWAVE_SPECULAR_UNIT); //xxx texture region coordinates are not used
	}
}

void Mesh::drawPicking(ICamera& camera) {
	if (isPickable()) {
		mProgram->use();

		core::Uniform::push(mULCModelMatrix, mPhysicsMMC);

		core::Uniform::push(mULCCameraPosition, camera.getTranslation());
		core::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());

		core::Uniform::push(mULCColorPicking, true);
		core::Uniform::push(mULCPainterColor, glm::vec4(getPickableColor(), 1.0));

		mVAO->bind();

		onDraw();

		mVAO->unbind();

		core::Uniform::push(mULCColorPicking, false);

		core::Program::disusePrograms();
	}
}

void Mesh::drawOcclusionBox(ICamera& camera) {

	mProgramOQ->use();

	core::Uniform::push(mULCMVPOcclusion,
			camera.getViewProjection() * mPhysicsMMC * mOcclusionMatrix);

	mOcclusionQuery.begin();

	glDrawArrays(GL_TRIANGLES, 0, gOQVertices);

	FLOG_CHECK("drawOcclusionBox failed");

	mOcclusionQuery.end();

	core::Program::disusePrograms();
}

void Mesh::drawDepth(ICamera& camera) {
	if (isPSC()) {
		mProgramShadow->use();

		core::Uniform::push(mULCMVPShadow,
				camera.getViewProjection() * mPhysicsMMC);

		mVAO->bind();

		onDraw();

		mVAO->unbind();

		core::Program::disusePrograms();
	}
}

void Mesh::drawDepthColor(ICamera& camera, glm::vec3& /*xxx double check position*/) {
	if (isPSC()) {
		mProgramShadowColor->use();

		core::Uniform::push(mULCMVPShadowColor,
				camera.getViewProjection() * mPhysicsMMC);
		core::Uniform::push(mULCModelMatrixShadowColor, mPhysicsMMC);

		mVAO->bind();

		onDraw();

		mVAO->unbind();

		core::Program::disusePrograms();
	}
}

void Mesh::drawAOG(ICamera& camera) {
	mProgramAOGeometry->use();

	core::Uniform::push(mULCMVPAmbientOcclusion,
			camera.getViewProjection() * mPhysicsMMC);
	core::Uniform::push(mULCPositionAmbientOcclusion,
			camera.getEye() * mPhysicsMMC);

	mVAO->bind();

	onDraw();

	mVAO->unbind();
}

void Mesh::drawAOC(ICamera& camera) {
	mProgramAOColor->use();

//      core::Uniform::push(mULCTextureMap, FILLWAVE_DIFFUSE_ATTACHMENT);
	core::Uniform::push(mULCSampleRadius, FILLWAVE_AO_SAMPLE_RADIUS);
	core::Uniform::push(mULCProjectionMatrix, camera.getProjection());
//      core::Uniform::push(mULCRandomVectors, camera.getEye() * mPhysicsMMC);

	mVAO->bind();

	onDraw();

	mVAO->unbind();
}

void Mesh::onDraw() {
	if (mIBO) {
		/* Perform index drawing */
		glDrawElements(mDrawType, mIBO->getElements(),
		GL_UNSIGNED_INT, (GLvoid*) 0);
		FLOG_CHECK("glDrawElements failed");
	} else {
		/* Perform array drawing */
		glDrawArrays(mDrawType, 0, mVBO->getElements());
		FLOG_CHECK("glDrawArrays failed");
	}
}

inline void Mesh::initPipeline() {
	if (mProgram) {
		ProgramLoader::initDefaultUniforms(mProgram.get());
	}
}

inline void Mesh::initUniformsCache() {
	/* Regular program */
	if (mProgram) {
		mULCModelMatrix = mProgram->getUniformLocation("uModelMatrix");
		mULCLightAmbientIntensity = mProgram->getUniformLocation(
				"uLightAmbientIntensity");
		mULCLightDiffuseIntensity = mProgram->getUniformLocation(
				"uLightDiffuseIntensity");
		mULCLightSpecularIntensity = mProgram->getUniformLocation(
				"uLightSpecularIntensity");
		mULCCameraPosition = mProgram->getUniformLocation("uCameraPosition");
		mULCViewProjectionMatrix = mProgram->getUniformLocation(
				"uViewProjectionMatrix");
		mULCColorPicking = mProgram->getUniformLocation("uColorPicking");
		mULCPainterColor = mProgram->getUniformLocation("uPainterColor");
	}
	/* Occlusion program */
	if (mProgramOQ) {
		mULCMVPOcclusion = mProgramOQ->getUniformLocation("uMVP");
	}

	/* Shadow program */
	if (mProgramShadow) {
		mULCMVPShadow = mProgramShadow->getUniformLocation("uMVP");
	}

	/* ShadowColor program */
	if (mProgramShadowColor) {
		mULCMVPShadowColor = mProgramShadowColor->getUniformLocation("uMVP");
		mULCModelMatrixShadowColor = mProgramShadowColor->getUniformLocation(
				"uModelMatrix");
	}

	/* AmbientOcclusion programs */
	if (mProgramAOGeometry) {
		mULCMVPAmbientOcclusion = mProgramAOGeometry->getUniformLocation("uMVP");
		mULCPositionAmbientOcclusion = mProgramAOGeometry->getUniformLocation(
				"uMVPosition");
	}

	if (mProgramAOColor) {
		mULCSampleRadius = mProgramAOColor->getUniformLocation("uSampleRadius");
		mULCProjectionMatrix = mProgramAOColor->getUniformLocation("uP");
	}
}

inline void Mesh::initBuffers() {
	if (mIBO) {
		FLOG_INFO("RELOAD IBO");
		mIBO->reload();
	}
	if (mVBO) {
		FLOG_INFO("RELOAD VBO");
		mVBO->reload();
	}
}

inline void Mesh::initVAO() {
	mSampler->bind();

	mVAO->bind();

	mVBO->bind();
	mVBO->attributesSetForVAO();
	mVBO->setReady();
	mVBO->send();

	if (mIBO) {
		mIBO->bind();
		mIBO->setReady();
		mIBO->send();
	}

	mVAO->unbind();
}

inline void Mesh::initVBO() {
	mVBO->getAttributes(mProgram->getHandle());
	mVBO->attributesBind(mProgram);
	mOcclusionMatrix = glm::scale(glm::mat4(1.0f), mVBO->getOcclusionBoxSize());
}

void Mesh::updateRenderpass(std::map<GLuint, std::vector<Entity*> >& renderpasses) {
	GLuint handle = mProgram.get()->getHandle();
	if (renderpasses.find(handle) != renderpasses.end()) {
		renderpasses[handle].push_back(this);
	} else {
		std::vector<Entity*> vector; /* xxx some base size maybe ? */
		vector.push_back(this);
		renderpasses[handle] = vector;
	}
}

void Mesh::log() const {
	mVBO->log();
}

} /* framework */
} /* fillwave */
