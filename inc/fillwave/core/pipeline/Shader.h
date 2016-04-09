/*
 * Shader.h
 *
 *  Created on: 28 Mar 2013
 *      Author: Filip Wasil
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <fillwave/core/GLObject.h>

#include <vector>
#include <string>
#include <memory>

namespace fillwave {
namespace core {

/*! \class Shader
 *
 * \brief Single GLSL shader object.
 *
 * - vertex shader
 * - geometry shader
 * - tesselation control shader
 * - tesselation evaluation shader
 * - fragment shader
 * - compute shader
 */

class Shader {
 public:
	Shader(GLuint shaderType, const std::string& shaderSource);

	virtual ~Shader();

	void compile();

	void loadSource();

	GLuint getType() {
		return mType;
	}

	std::string getTypeString();

	std::string getSource() {
		return mSource;
	}

	GLuint getHandle() {
		return mHandle;
	}

	void log();

	void reload();

 private:
	GLuint mHandle;

	GLuint mType;

	std::string mSource;
};

} /* core */
} /* fillwave */

std::vector<fillwave::core::Shader*> operator+(
   std::vector<fillwave::core::Shader*> shaders,
   fillwave::core::Shader* shader2);

#endif /* SHADER_H_ */
