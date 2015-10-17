/*
 * EmiterPoint.h
 *
 *  Created on: 16 Jun 2014
 *      Author: Filip Wasil
 */

#ifndef EMITERPOINT_H_
#define EMITERPOINT_H_

#include <fillwave/models/Entity.h>
#include <fillwave/core/buffers/VertexBufferParticles.h>
#include <fillwave/core/buffers/IndexBufferParticles.h>
#include <fillwave/core/pipeline/Program.h>
#include <fillwave/core/texturing/Texture.h>
#include <fillwave/core/rendering/TransformFeedback.h>
#include <fillwave/common/Blending.h>
#include <fillwave/models/Reloadable.h>

namespace fillwave {
class Engine;
namespace particles {

/*! \class EmiterPoint
 *
 * \brief Drawable Entity which emits particles.
 *
 */

class EmiterPoint: public models::Entity, public models::Reloadable {
public:
	EmiterPoint(
			Engine* engine,
			GLuint howMany,
			GLfloat size,
			GLfloat lifetime,
			pTexture texture,
			glm::vec4 color,
			GLenum blendingSource,
			GLenum blendingDestination,
			GLboolean depthTesting,
			GLfloat alphaCutOff);

	virtual ~EmiterPoint() = default;

	virtual void update(GLfloat timeElapsedSec) = 0;

	virtual void draw(space::Camera& camera) = 0;

	void setBlendingFunction(GLenum sourceFactor, GLenum destinationFactor);

protected:
	GLfloat mLifetime;
	GLfloat mStartSize;
	GLfloat mHowMany;
	GLboolean mDepthTesting;

	glm::vec4 mColor;
	common::Blending mBlending;
	GLfloat mAlphaCutOff;

	pProgram mProgram;
	pIndexBufferParticles mIBO;
	pTexture mTexture;

};

} /* particles */
typedef std::shared_ptr<particles::EmiterPoint> pEmiterPoint;
} /* fillwave */

#endif /* EMITERPOINT_H_ */
