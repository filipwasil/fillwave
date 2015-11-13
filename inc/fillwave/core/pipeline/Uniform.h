/*
 * Uniform.h
 *
 *  Created on: May 11, 2014
 *      Author: Filip Wasil
 */

#ifndef UNIFORM_H_
#define UNIFORM_H_

#include <fillwave/OpenGL.h>

#include <fillwave/Math.h>

#include <string>
#include <memory>

#define FILLWAVE_UNIFORM_NOT_FOUND -1

namespace fillwave {
namespace core {

/*! \type UniformData
 * \brief Uniform data structure.
 */

typedef union UniformData {
	GLenum glEnum;
	GLbitfield glBitfield;
	GLuint glUint;
	GLint glInt;
	GLsizei glSizei;
	GLboolean glBoolean;
	GLbyte glByte;
	GLshort glShort;
	GLubyte glUbyte;
	GLushort glUshort;
	//GLulong glUlong;
	GLfloat glFloat;
	GLfloat glVec2[2];
	GLfloat glVec3[3];
	GLfloat glVec4[4];
	GLfloat glMat2[4];
	GLfloat glMat3[9];
	GLfloat glMat4[16];
} UniformData;

/*! \class Uniform
 * \brief Uniform.
 */

class Uniform {
public:
	Uniform(std::string name, GLuint type, GLsizei size, GLint location);

	virtual ~Uniform() = default;

	GLboolean isName(std::string& name) const;

	GLuint getType() const;

	GLsizei getSize() const;

	GLint getLocation() const;

	void setName(std::string name);
	void setType(GLuint size);
	void setSize(GLsizei size);
	void setLocation(GLint location);
	void setData(UniformData data);

	/* Slow push with O(n) where n is uniform vector size */

	void push(GLint value);
	void push(GLint* value, GLint size);
	void push(GLfloat value);
	void push(GLfloat* value, GLint size);
	void push(glm::mat4 value);
	void push(glm::mat4* value, GLuint size);
	void push(glm::mat3 value);
	void push(glm::mat2 value);
	void push(glm::vec2 value);
	void push(glm::vec3 value);
	void push(glm::vec3* value, GLuint size);
	void push(glm::vec4 value);

	/* Fast push with O(1) */

	static void push(GLint location, GLint data);
	static void push(GLint location, GLint* data, GLint count);
	static void push(GLint location, GLfloat data);
	static void push(GLint location, GLfloat* data, GLint count);
	static void push(GLint location, glm::mat2 data);
	static void push(GLint location, glm::mat3 data);
	static void push(GLint location, glm::mat4 data);
	static void push(GLint location, glm::mat4* data, GLuint size);
	static void push(GLint location, glm::vec2 data);
	static void push(GLint location, glm::vec3 data);
	static void push(GLint location, glm::vec4 data);

	void log() const;

private:
	std::string mName;
	GLenum mType;
	GLsizei mSize;
	GLint mLocation;
	UniformData mData;
};

} /* core */
typedef std::unique_ptr<core::Uniform> puUniform;
} /* fillwave */

#endif /* UNIFORM_H_ */
