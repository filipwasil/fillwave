/*
 * Sampler.cpp
 *
 *  Created on: Mar 30, 2014
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * filip.wasil@gmail.com
 *
 */

#include <fillwave/core/texturing/Sampler.h>
#include <fillwave/extras/Log.h>

FLOGINIT("Sampler", FERROR | FFATAL)

namespace fillwave {
namespace core {

Sampler::Sampler(GLint textureUnit, GLuint howMany)
		: GLObject(howMany), mTextureUnit(textureUnit) {
	glGenSamplers(mHowMany, mHandles);
	FLOG_CHECK("ERROR: Could not generate sampler -> ID");
}

Sampler::~Sampler() {
	glDeleteSamplers(mHowMany, mHandles);
}

//xxx not needed
//void Sampler::bind(GLuint textureUnit, GLuint id) {
//   glBindSampler(textureUnit, mHandles[id]);
//   FLOG_CHECK("Could not bind the Sampler");
//}

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
