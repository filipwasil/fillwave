/*
 * Shader.cpp
 *
 *  Created on: 28 Mar 2014
 *      Author: Filip Wasil
 */

#include <fillwave/core/pipeline/Shader.h>
#include <fillwave/extras/Log.h>

#include <string>

FLOGINIT("Shader", FERROR | FFATAL | FINFO | FDEBUG)

using namespace std;

namespace fillwave {
namespace core {

Shader::Shader(GLuint shaderType, const std::string& shaderSource)
		: mType(shaderType), mSource(shaderSource) {
	reload();
}

Shader::~Shader() {
	glDeleteShader(mHandle);
	FLOG_CHECK("Shader destructor");
}

void Shader::loadSource() {
	if (not mSource.empty()) {
		const GLchar *source = (const GLchar *) mSource.c_str();
		glShaderSource(mHandle, 1, &source, nullptr);
		FLOG_CHECK("Loading source code to the shader failed");
	} else {
		FLOG_FATAL("Shader not found, or empty");
	}
}

void Shader::compile() {
	glCompileShader(mHandle);

	GLint status = 0;
	glGetShaderiv(mHandle, GL_COMPILE_STATUS, &status);
	FLOG_DEBUG("Compilation status: %d", status);
	if (!status) {
		// There was an error, print it out
		GLint infoLogLength = 0;
		glGetShaderiv(mHandle, GL_INFO_LOG_LENGTH, &infoLogLength);

		char* pShaderInfoLog = new char[infoLogLength];
		if (pShaderInfoLog) {
			glGetShaderInfoLog(mHandle, infoLogLength, NULL, pShaderInfoLog);
			FLOG_ERROR("Compilation: %s", pShaderInfoLog);
			delete pShaderInfoLog;
		}
		glDeleteShader(mHandle);
		mHandle = 0;
		FLOG_FATAL(
				"Shader can not bee compiled\n--------------------------------------------------\n"
						"%s \n--------------------------------------------------\n",
				mSource.c_str());
	}
}

void Shader::log() {
	int infologLength = 0;
	int maxLength;

	if (glIsShader(mHandle)) {
		glGetShaderiv(mHandle, GL_INFO_LOG_LENGTH, &maxLength);
	} else {
		glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &maxLength);
	}
	std::vector<char> infoLog(maxLength);

	if (glIsShader(mHandle)) {
		glGetShaderInfoLog(mHandle, maxLength, &infologLength, infoLog.data());
	} else {
		glGetProgramInfoLog(mHandle, maxLength, &infologLength, infoLog.data());
	}

	if (infologLength > 0) {
		FLOG_INFO("%s\n", infoLog.data());
	}
	FLOG_INFO("%s\n", mSource.c_str());
}

void Shader::reload() {
	mHandle = glCreateShader(mType);
	FLOG_CHECK("Shader compilation failed: %x", glGetError());
	loadSource();
	compile();
}

std::string Shader::getTypeString() {
	switch (mType) {
		case GL_FRAGMENT_SHADER:
			return "GL_FRAGMENT_SHADER";
		case GL_VERTEX_SHADER:
			return "GL_VERTEX_SHADER";
#ifdef __ANDROID__
#else
		case GL_GEOMETRY_SHADER:
			return "GL_GEOMETRY_SHADER";
		case GL_TESS_CONTROL_SHADER:
			return "GL_TESS_CONTROL_SHADER";
		case GL_TESS_EVALUATION_SHADER:
			return "GL_TESS_EVALUATION_SHADER";
#endif
		default:
			FLOG_FATAL("Shader type not recognized: %d", mType);
			return "";
	}
}

} /* core */
} /* fillwave */

std::vector<fillwave::pShader> operator+(
		fillwave::pShader shader1,
		fillwave::pShader shader2) {
	std::vector<fillwave::pShader> shaders;
	shaders.push_back(shader1);
	shaders.push_back(shader2);
	return shaders;
}

std::vector<fillwave::pShader> operator+(
		std::vector<fillwave::pShader> shaders,
		fillwave::pShader shader) {
	shaders.push_back(shader);
	return shaders;
}

