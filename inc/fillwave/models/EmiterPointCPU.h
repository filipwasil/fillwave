/*
 * EmiterPointCPU.h
 *
 *  Created on: Sep 10, 2014
 *      Author: Filip Wasil
 */

#ifndef EMITER_POINT_CPU_H_
#define EMITER_POINT_CPU_H_

#include <fillwave/core/buffers/VertexBufferFloat.h>
#include <fillwave/core/operations/TQuery.h>
#include <fillwave/models/base/IEmiterPoint.h>

namespace fillwave {
namespace framework {

/*! \class EmiterPointCPU
 * \brief Polynomial particle Emiter.
 * Can generate a particles with velocity, direction,
 * and acceleration defined by the user.
 */

class EmiterPointCPU: public IEmiterPoint {
  public:
	EmiterPointCPU(
	    Engine* engine,
	    GLfloat emitingSourceRate,
	    GLuint howMany,
	    glm::vec4 color,
	    glm::vec3 acceleration = glm::vec3(0.0),
	    glm::vec3 startVelocity = glm::vec3(0.0),
	    glm::vec3 robustnessVelocity = glm::vec3(0.0),
	    glm::vec3 startPosition = glm::vec3(0.0),
	    glm::vec3 robustnessPosition = glm::vec3(0.0),
	    GLfloat startSize = 1.0,
	    GLfloat lifetime = 6.0,
	    core::Texture* texture = nullptr,
	    GLenum blendingSource = GL_SRC_ALPHA,
	    GLenum blendingDestination = GL_ONE_MINUS_SRC_ALPHA,
	    GLboolean depthTesting = GL_TRUE,
	    GLfloat alphaCutOffLevel = 0.0f);

	virtual ~EmiterPointCPU() = default;

	/* IEmiterPoint */
	void update(GLfloat timeElapsedSec);

	/* IDrawable */
	void draw(ICamera& camera) override;
	void drawPBRP(ICamera& camera) override;

	/* IRenderable */
	bool getRenderItem(RenderItem& item) override;

  private:
	glm::vec3 mAcceleration;
	glm::vec3 mStartVelocity;
	glm::vec3 mStartPosition;
	glm::vec3 mCameraPosition;

	/* ULC - Uniform location cache */
	pVertexBufferParticles mVBO;
	GLint mULCModelMatrix, mULCTextureUnit, mULCViewProjectionMatrix,
	      mULCCameraPosition, mULCPointSize, mULCColor, mULCAcceleration,
	      mULCLifeTime, mULCAlphaCutOff, mULCSourcePosition, mULCTimeElapsed;

	void initBuffers();
	void initPipeline();
	void initUniformsCache();
	void initVAO();
	void initVBO();
	void coreDraw();
};

} /* framework */
} /* fillwave */

#endif /* EMITER_POINT_CPU_H_ */
