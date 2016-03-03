/*
 * Uniform.cpp
 *
 *  Created on: May 11, 2014
 *      Author: filip
 */

#include <fillwave/core/pipeline/Uniform.h>
#include <fillwave/Log.h>
#include <string>

FLOGINIT("Uniform", FERROR | FFATAL | FINFO)

namespace fillwave {
namespace core {

Uniform::Uniform(std::string name, GLuint type, GLsizei size, GLint location) :
		mName(name), mType(type), mSize(size), mLocation(location) {
	/* xxx validate parameters */
}

GLboolean Uniform::isName(std::string& name) const {
	return mName == name;
}

GLint Uniform::getLocation() const {
	return mLocation;
}

/* TODO make a template here */
template <class T>
void pushToProgram(T value);

void Uniform::push(GLint value) {
	glUniform1i(mLocation, value);
	FLOG_CHECK("Uniform push failed");
}
void Uniform::push(GLint* value, GLint size) {
	glUniform1iv(mLocation, size, value);
	FLOG_CHECK("Uniform push failed");
}
void Uniform::push(GLfloat value) {
	glUniform1f(mLocation, value);
	FLOG_CHECK("Uniform push failed");
}
void Uniform::push(GLfloat* value, GLint size) {
	glUniform1fv(mLocation, size, value);
	FLOG_CHECK("Uniform push failed");
}
void Uniform::push(glm::vec2 value) {
	glUniform2fv(mLocation, 1, glm::value_ptr(value));
	FLOG_CHECK("Uniform push failed");
}
void Uniform::push(glm::vec3 value) {
	glUniform3fv(mLocation, 1, glm::value_ptr(value));
	FLOG_CHECK("Uniform push failed");
}
void Uniform::push(glm::vec4 value) {
	glUniform4fv(mLocation, 1, glm::value_ptr(value));
	FLOG_CHECK("Uniform push failed");
}
void Uniform::push(glm::mat2 value) {
	glUniformMatrix2fv(mLocation, 1, GL_FALSE, glm::value_ptr(value));
	FLOG_CHECK("Uniform push failed");
}
void Uniform::push(glm::mat3 value) {
	glUniformMatrix3fv(mLocation, 1, GL_FALSE, glm::value_ptr(value));
	FLOG_CHECK("Uniform push failed");
}
void Uniform::push(glm::mat4 value) {
	glUniformMatrix4fv(mLocation, 1, GL_FALSE, glm::value_ptr(value));
	FLOG_CHECK("Uniform push failed");
}
void Uniform::push(glm::vec3* value, GLuint size) {
	glUniform3fv(mLocation, size, (GLfloat*) value);
	FLOG_CHECK("Uniform push failed");
}
void Uniform::push(glm::mat4* value, GLuint size) {
	glUniformMatrix4fv(mLocation, size, GL_FALSE, (GLfloat*) value);
	FLOG_CHECK("Uniform push failed");
}

/* Direct method */

void Uniform::push(GLint location, GLint data) {
	if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
		FLOG_ERROR("No int uniform under location %d", location);
	} else {
		glUniform1i(location, data);
		FLOG_CHECK("Uniform int push failed");
	}
}

void Uniform::push(GLint location, GLint* data, GLint count) {
	if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
		FLOG_ERROR("No int uniform under location %d", location);
	} else {
		glUniform1iv(location, count, data);
		FLOG_CHECK("Uniform var int push failed");
	}
}

void Uniform::push(GLint location, GLfloat data) {
	if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
		FLOG_ERROR("No int uniform under location %d", location);
	} else {
		glUniform1f(location, data);
		FLOG_CHECK("Uniform float push failed");
	}
}

void Uniform::push(GLint location, GLfloat* data, GLint count) {
	if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
		FLOG_ERROR("No int uniform under location %d", location);
	} else {
		glUniform1fv(location, count, data);
		FLOG_CHECK("Uniform var float push failed");
	}
}

void Uniform::push(GLint location, glm::vec2 data) {
	if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
		FLOG_ERROR("No int uniform under location %d", location);
	} else {
		glUniform2fv(location, 1, glm::value_ptr(data));
		FLOG_CHECK("Uniform vec2 push failed");
	}
}

void Uniform::push(GLint location, glm::vec3 data) {
	if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
		FLOG_ERROR("No int uniform under location %d", location);
	} else {
		glUniform3fv(location, 1, glm::value_ptr(data));
		FLOG_CHECK("Uniform vec3 push failed");
	}
}

void Uniform::push(GLint location, glm::vec4 data) {
	if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
		FLOG_ERROR("No int uniform under location %d", location);
	} else {
		glUniform4fv(location, 1, glm::value_ptr(data));
		FLOG_CHECK("Uniform vec4 push failed");
	}
}

void Uniform::push(GLint location, glm::mat2 data) {
	if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
		FLOG_ERROR("No int uniform under location %d", location);
	} else {
		glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(data));
		FLOG_CHECK("Uniform mat2 push failed");
	}
}

void Uniform::push(GLint location, glm::mat3 data) {
	if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
		FLOG_ERROR("No int uniform under location %d", location);
	} else {
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(data));
		FLOG_CHECK("Uniform mat3 push failed");
	}
}

void Uniform::push(GLint location, glm::mat4 data) {
	if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
		FLOG_ERROR("No int uniform under location %d", location);
	} else {
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(data));
		FLOG_CHECK("Uniform mat4 push failed");
	}
}

void Uniform::push(GLint location, glm::mat4* data, GLuint size) {
	if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
		FLOG_ERROR("No int uniform under location %d", location);
	} else {
		glUniformMatrix4fv(location, size,
		GL_FALSE, reinterpret_cast<GLfloat*>(data));
		FLOG_CHECK("Uniform var mat4 push failed");
	}
}

void Uniform::setName(std::string name) {
	mName = name;
}

GLuint Uniform::getType() const {
	return mType;
}

void Uniform::setType(GLuint type) {
	mType = type;
}

GLsizei Uniform::getSize() const {
	return mSize;
}

void Uniform::setSize(GLsizei size) {
	mSize = size;
}

void Uniform::setLocation(GLint location) {
	mLocation = location;
}

void Uniform::setData(UniformData data) {
	mData = data;
}

void Uniform::log() const {
	FLOG_INFO("Name: %s", mName.c_str());
	FLOG_INFO("Location: %d", mLocation);
	FLOG_INFO("Type: 0x%x", mType);
	FLOG_INFO("Size: %d", mSize);
}

} /* core */
} /* fillwave */
