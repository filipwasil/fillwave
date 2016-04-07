/*
 * EmiterPointGPU.h
 *
 *  Created on: 22 Apr 2015
 *      Author: Filip Wasil
 */

#ifndef EMITERPOINTGPU_H_
#define EMITERPOINTGPU_H_

#include <fillwave/core/buffers/VertexBufferParticlesGPU.h>
#include <fillwave/core/pipeline/Fence.h>
#include <fillwave/models/base/IEmiterPoint.h>

namespace fillwave {
class Engine;
namespace framework {

/*! \class EmiterPointGPU
 * \brief Polynomial particle Emiter entirely computed on GPU.
 * Can generate a particles with velocity, direction,
 * and acceleration defined by the user.
 */

class EmiterPointGPU: public IEmiterPoint {
public:
	EmiterPointGPU(
			Engine* engine,
			GLfloat emitingSourceRate,
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
			GLfloat alphaCutOffLevel = 0.0f);

	virtual ~EmiterPointGPU() = default;

	/* IEmiterPoint */
	void update(GLfloat timeElapsedSec);

	/* IDrawable */
	void draw(ICamera& camera) override;
	void drawPBRP(ICamera& camera) override;

	/* IRenderable */
	bool getRenderItem(RenderItem& item) override;

private:
	static const GLint mPingPongBuffers = 2;
	GLuint mSrcIndex;
	GLuint mNoiseTextureHandle;
	GLfloat mEmmisingSourceRate;
	glm::vec3 mAcceleration;
	glm::vec3 mStartVelocity;
	glm::vec3 mRobustnessVelocity;
	glm::vec3 mStartPosition;
	glm::vec3 mRobustnessPosition;
	glm::vec3 mCameraPosition;
	GLfloat mTimeDeltaEmiter;
	pProgram mProgramEmiter;
	puFence mFence;

	pVertexBufferParticlesGPU mVBOGPU[mPingPongBuffers];

	GLint mULCTimeEmiter, mULCEmissionRateEmiter, mULCModelMatrixEmiter,
			mULCCameraPositionEmiter, mULCHowManyEmiter, mULCAccelerationEmiter,
			mULCStartVelocityEmiter, mULCStartPositionEmiter, mULCLifeTimeEmiter,
			mULCRobustnessVelocityEmiter, mULCRobustnessPositionEmiter,
			mULCNoiseSamplerEmiter;

	GLint mULCModelMatrix, mULCViewProjectionMatrix, mULCCameraPosition,
			mULCTextureUnit, mULCTime, mULCAcceleration, mULCColor,
			mULCAlphaCutOff, mULCStartSize;

	void initBuffers();
	void initPipeline();
	void initVBO();
	void initVAO();
	void initUniformsCache();
	void coreDraw();

	void sort(glm::vec3 cameraPosition);
};

} /* particles */
typedef std::shared_ptr<framework::EmiterPointGPU> pEmiterPointGPU;
} /* fillwave */

#endif /* EMITERPOINTGPU_H_ */
