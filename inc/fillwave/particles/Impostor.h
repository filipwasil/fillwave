/*
 * Impostor.h
 *
 *  Created on: May 10, 2014
 *      Author: Filip Wasil
 */

#ifndef IMPOSTOR_H_
#define IMPOSTOR_H_

#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/core/texturing/Sampler.h>
#include <fillwave/core/pipeline/Program.h>

#include <fillwave/common/Finishable.h>
#include <fillwave/common/Blending.h>

#include <fillwave/models/Entity.h>

namespace fillwave {
class Engine;
namespace particles {

/*! \class Impostor
 * \brief Drawable Entity built by fragment shader. Time limited.
 */

class Impostor: public models::Entity, public common::Finishable {
private:
	pTexture mTexture;
	pSampler mSampler;
	common::Blending mBlending;
protected:
	pProgram mProgram;
	GLfloat mSize;

	void coreDraw();

public:
	Impostor(
			Engine* engine,
			GLfloat lifetime,
			GLfloat size,
			pTexture texture = pTexture(),
			GLenum blendingSource = GL_SRC_ALPHA,
			GLenum blendingDestination = GL_ONE_MINUS_SRC_ALPHA);
	virtual ~Impostor() = default;
	virtual void draw(space::Camera& camera);
};

} /* models */
typedef std::shared_ptr<particles::Impostor> pImpostor;
} /* fillwave */

#endif /* IMPOSTOR_H_ */
