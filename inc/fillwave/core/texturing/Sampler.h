/*
 * Sampler.h
 *
 *  Created on: Mar 30, 2014
 *      Author: Filip Wasil
 */

#ifndef SAMPLER_H_
#define SAMPLER_H_

#include <fillwave/core/GLObject.h>
#include <fillwave/core/texturing/Parameter.h>
#include <memory>

namespace fillwave {
namespace core {

/*! \class Sampler
 * \brief SamplerObject - SO.
 */

class Sampler: public GLObject {
 public:
	Sampler(GLint textureUnit, GLuint howMany = 1);

	virtual ~Sampler();

	void bind(GLuint id = 0);

	void unbind(GLuint id = 0);

	void setParameters(ParameterList parameters);

	void setParameter(GLenum parameter, GLenum value, GLuint id = 0);

	void setParameter(Parameter parameter, GLuint id = 0);

	void reload();

	GLint getTextureUnit();

 private:
	GLint mTextureUnit;
};

} /* core */
} /* fillwave */

#endif /* SAMPLER_H_ */
