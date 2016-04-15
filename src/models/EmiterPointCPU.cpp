/*
 * EmiterPointCPU.cpp

 *
 *  Created on: Sep 10, 2014
 *      Author: filip
 */

#include <fillwave/models/EmiterPointCPU.h>
#include <fillwave/loaders/ProgramLoader.h>

#include <fillwave/Fillwave.h>

FLOGINIT("EmiterPointCPU", FERROR | FFATAL | FINFO)

namespace fillwave {
namespace framework {

EmiterPointCPU::EmiterPointCPU(Engine* engine,
                               GLfloat /*emitingSourceRate*/, //xxx not used for now
                               GLuint howMany,
                               glm::vec4 color,
                               glm::vec3 acceleration,
                               glm::vec3 startVelocity,
                               glm::vec3 robustnessVelocity,
                               glm::vec3 startPosition,
                               glm::vec3 robustnessPosition,
                               GLfloat startSize,
                               GLfloat lifetime,
                               core::Texture* texture,
                               GLenum blendingSource,
                               GLenum blendingDestination,
                               GLboolean depthTesting,
                               GLfloat alphaCutOffLevel) :
	IEmiterPoint(engine, howMany, startSize, lifetime, texture, color,
	             blendingSource, blendingDestination, depthTesting,
	             alphaCutOffLevel),
	mAcceleration(acceleration),
	mStartVelocity(startVelocity),
	mStartPosition(startPosition) {

	ProgramLoader loader(engine);

	mProgram = loader.getParticleCPU();

	/* Fill buffers */
	GLfloat time = 0.0f; // start time
	std::vector<GLfloat> times;
	std::vector<GLfloat> positions;
	std::vector<GLfloat> velocities;
	std::vector<GLfloat> cameraDistanceTF;

	times.reserve(howMany);
	positions.reserve(3 * howMany);
	velocities.reserve(3 * howMany);
	cameraDistanceTF.reserve(howMany);

	for (GLuint i = 0; i < howMany; i++) {

		times.push_back(time);
		time += 1.0f / lifetime;

		/* particles velocity */
		GLfloat x = (((GLfloat) rand() / (GLfloat) RAND_MAX))
		            * robustnessVelocity.x * 1.0f - robustnessVelocity.x * 0.5f;
		GLfloat y = (((GLfloat) rand() / (GLfloat) RAND_MAX))
		            * robustnessVelocity.y * 1.0f - robustnessVelocity.y * 0.5f;
		GLfloat z = (((GLfloat) rand() / (GLfloat) RAND_MAX))
		            * robustnessVelocity.z * 1.0f - robustnessVelocity.z * 0.5f;
		velocities.push_back(x);
		velocities.push_back(y);
		velocities.push_back(z);

		/* emiter surface shape */
		x = ((GLfloat) rand() / (GLfloat) RAND_MAX) * robustnessPosition.x * 1.0f
		    - robustnessPosition.x * 0.5f;
		y = ((GLfloat) rand() / (GLfloat) RAND_MAX) * robustnessPosition.y * 1.0f
		    - robustnessPosition.y * 0.5f;
		z = ((GLfloat) rand() / (GLfloat) RAND_MAX) * robustnessPosition.z * 1.0f
		    - robustnessPosition.z * 0.5f;
		positions.push_back(x);
		positions.push_back(y);
		positions.push_back(z);

		cameraDistanceTF.push_back(0.0);
	}

	/* Initialize OpenGL stuff */
	mVBO = engine->storeBuffer<core::VertexBufferParticles>(mVAO, velocities, positions, times);
   mIBO = engine->storeBuffer<core::IndexBuffer>(mVAO, howMany);

	initPipeline();
	initVBO();
	initVAO();
	initUniformsCache();
}

void EmiterPointCPU::update(GLfloat timeElapsedSec) {
	mProgram->use();
	core::Uniform::push(mULCTimeElapsed, timeElapsedSec);
	core::Program::disusePrograms();
}

void EmiterPointCPU::draw(ICamera& camera) {
	mCameraPosition = camera.getTranslation();

	mProgram->use();

	core::Uniform::push(mULCModelMatrix, mPhysicsMMC);
	core::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());
	core::Uniform::push(mULCCameraPosition, mCameraPosition);
	core::Uniform::push(mULCPointSize, mStartSize);
	core::Uniform::push(mULCColor, mColor);
	core::Uniform::push(mULCAcceleration, mAcceleration);
	core::Uniform::push(mULCLifeTime, mLifetime);
	core::Uniform::push(mULCAlphaCutOff, mAlphaCutOff);
//   core::Uniform::push(mULCSourcePosition, mTranslation);

	coreDraw();

	core::Program::disusePrograms();
}

void EmiterPointCPU::drawPBRP(ICamera& camera) {
	mCameraPosition = camera.getTranslation();

	core::Uniform::push(mULCModelMatrix, mPhysicsMMC);
	core::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());
	core::Uniform::push(mULCCameraPosition, mCameraPosition);
	core::Uniform::push(mULCPointSize, mStartSize);
	core::Uniform::push(mULCColor, mColor);
	core::Uniform::push(mULCAcceleration, mAcceleration);
	core::Uniform::push(mULCLifeTime, mLifetime);
	core::Uniform::push(mULCAlphaCutOff, mAlphaCutOff);
//   core::Uniform::push(mULCSourcePosition, mTranslation);

	coreDraw();
}

inline void EmiterPointCPU::coreDraw() {

	mVAO->bind();

	if (mTexture) {
		mTexture->bind(FILLWAVE_DIFFUSE_UNIT);
	}

	if (not mDepthTesting) {
		glDepthMask(GL_FALSE);
	}

	glEnable(GL_BLEND);
	glBlendFunc(mBlending.mSrc, mBlending.mDst);
//   glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
//   glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
	glDrawElements(GL_POINTS, mIBO->getElements(), GL_UNSIGNED_INT,
	               reinterpret_cast<GLvoid*>(0));
	FLOG_CHECK("Draw elements");
	glDisable(GL_BLEND);
	if (not mDepthTesting) {
		glDepthMask(GL_TRUE);
	}

	core::Texture2D::unbind2DTextures();

	core::VertexArray::unbindVAO();
}

void EmiterPointCPU::initBuffers() {
	if (mIBO) {
		mIBO->reload();
	}
	if (mVBO) {
		mVBO->reload();
	}
}

void EmiterPointCPU::initPipeline() {
	mProgram->use();
	mProgram->uniformPush("uTextureUnit", FILLWAVE_DIFFUSE_UNIT);
	core::Program::disusePrograms();
}

void EmiterPointCPU::initUniformsCache() {
	mULCTimeElapsed = mProgram->getUniformLocation("uTimeElapsed");
	mULCModelMatrix = mProgram->getUniformLocation("uModelMatrix");
	mULCViewProjectionMatrix = mProgram->getUniformLocation(
	                              "uViewProjectionMatrix");
	mULCCameraPosition = mProgram->getUniformLocation("uCameraPosition");
	mULCPointSize = mProgram->getUniformLocation("uPointSize");
	mULCColor = mProgram->getUniformLocation("uColor");
	mULCAcceleration = mProgram->getUniformLocation("uAcceleration");
	mULCLifeTime = mProgram->getUniformLocation("uLifeTime");
	mULCAlphaCutOff = mProgram->getUniformLocation("uAlphaCutOff");
//   mULCSourcePosition = mProgram->getUniformLocation("uSourcePosition");
	mULCTextureUnit = mProgram->getUniformLocation("uTextureUnit");
}

void EmiterPointCPU::initVAO() {
	mSampler->bind();
	mVAO->bind();
	mVBO->bind();
	mVBO->setLoaded(GL_FALSE);
	mVBO->send();
	mVBO->attributesSetForVAO();
	mIBO->bind();
	mIBO->setLoaded(GL_FALSE);
	mIBO->send();
	core::VertexArray::unbindVAO();
}

void EmiterPointCPU::initVBO() {
    mVBO->initAttributes(mProgram->getHandle());
}

bool EmiterPointCPU::getRenderItem(RenderItem& item) {
	item.mBlend = mBlending;
	item.mCount = mIBO->getElements();
	item.mDataType = GL_UNSIGNED_INT;
	item.mFirst = 0;
	item.mHandles[RenderItem::eRenderHandleProgram] = mProgram->getHandle();
	item.mHandles[RenderItem::eRenderHandleSampler] = mSampler->getHandle();
	item.mHandles[RenderItem::eRenderHandleVAO] = mVAO->getHandle();
	item.mHandles[RenderItem::eRenderHandleDiffuse] = mTexture->getHandle();
	item.mIndicesPointer = 0;
	item.mMode = GL_POINTS;

	item.mRenderStatus = 0xe4; // 11100100
	return true;
}

} /* framework */
} /* fillwave */
