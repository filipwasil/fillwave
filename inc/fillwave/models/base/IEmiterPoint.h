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
#include <fillwave/models/base/Reloadable.h>

namespace fillwave {
class Engine;
namespace framework {

/*! \class EmiterPoint
 * \brief Drawable Entity which emits particles.
 */

class IEmiterPoint: public Entity, public Reloadable {
public:
	IEmiterPoint(
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

	virtual ~IEmiterPoint() = default;

	void updateRenderer(IRenderer& renderer);
	void setBlendingFunction(GLenum sourceFactor, GLenum destinationFactor);

	virtual void update(GLfloat timeElapsedSec) = 0;
	virtual void draw(ICamera& camera) = 0;

protected:
	GLfloat mStartSize;
	GLfloat mLifetime;
	pTexture mTexture;
	glm::vec4 mColor;
	GLfloat mHowMany;
	GLboolean mDepthTesting;
	GLfloat mAlphaCutOff;
	Blending mBlending;
	pProgram mProgram;
	pIndexBufferParticles mIBO;
};

} /* framework */
typedef std::shared_ptr<framework::IEmiterPoint> pIEmiterPoint;
} /* fillwave */

#endif /* EMITERPOINT_H_ */
