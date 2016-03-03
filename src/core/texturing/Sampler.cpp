/*
 * Sampler.cpp
 *
 *  Created on: Mar 30, 2014
 *      Author: filip
 */

#include <fillwave/core/texturing/Sampler.h>
#include <fillwave/Log.h>

FLOGINIT("Sampler", FERROR | FFATAL)

namespace fillwave {
namespace core {

Sampler::Sampler(GLint textureUnit, GLuint howMany) :
		GLObject(howMany), mTextureUnit(textureUnit) {
	glGenSamplers(mHowMany, mHandles);
	FLOG_CHECK("ERROR: Could not generate sampler -> ID");
}

Sampler::~Sampler() {
	glDeleteSamplers(mHowMany, mHandles);
}

void Sampler::bind(GLuint id) {
	glBindSampler(mTextureUnit, mHandles[id]);
	FLOG_CHECK("Could not bind the Sampler");
}

void Sampler::unbind(GLuint id) {
	glBindSampler(0, mHandles[id]);
	FLOG_CHECK("Could not bind the VAO");
}

void Sampler::setParameters(ParameterList parameters) {
	for (auto it : parameters) {
		setParameter(it.first, it.second);
	}
}

void Sampler::setParameter(GLenum parameter, GLenum value, GLuint id) {
	glSamplerParameteri(mHandles[id], parameter, value);
	FLOG_CHECK("setParameter: 0x%x", parameter);
}

void Sampler::setParameter(Parameter parameter, GLuint id) {
	glSamplerParameteri(mHandles[id], parameter.first, parameter.second);
	FLOG_CHECK("setParameter");
}

GLint Sampler::getTextureUnit() {
	return mTextureUnit;
}

void Sampler::reload() {
	glGenSamplers(mHowMany, mHandles);
	FLOG_CHECK("reload");
}

} /* core */
} /* fillwave */
