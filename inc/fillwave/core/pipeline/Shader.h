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
typedef std::shared_ptr<core::Shader> pShader;
} /* fillwave */

std::vector<fillwave::pShader> operator+(
    fillwave::pShader shader1,
    fillwave::pShader shader2);
std::vector<fillwave::pShader> operator+(
    std::vector<fillwave::pShader> shaders,
    fillwave::pShader shader2);

#endif /* SHADER_H_ */
