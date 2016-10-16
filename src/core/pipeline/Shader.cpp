/*
 * Shader.cpp
 *
 *  Created on: 28 Mar 2014
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <fillwave/core/pipeline/Shader.h>
#include <fillwave/Log.h>
#include <sstream>

FLOGINIT("Shader", FERROR | FFATAL | FINFO | FDEBUG)

using namespace std;

namespace fillwave {
namespace core {

Shader::Shader(GLuint shaderType, const std::string& shaderSource) :
	mType(shaderType), mSource(shaderSource) {
	reload();
}

Shader::~Shader() {
	glDeleteShader(mHandle);
	fLogC("Shader destructor");
}

void Shader::loadSource() {
	if (not mSource.empty()) {
		const GLchar *source = (const GLchar *) mSource.c_str();
		glShaderSource(mHandle, 1, &source, nullptr);
		fLogC("Loading source code to the shader failed");
	} else {
		fLogF("Shader not found, or empty");
	}
}

void Shader::compile() {
	glCompileShader(mHandle);

	GLint status = 0;
	glGetShaderiv(mHandle, GL_COMPILE_STATUS, &status);
	fLogD("Compilation status: %d", status);
	if (!status) {
		// There was an error, print it out
		GLint infoLogLength = 0;
		glGetShaderiv(mHandle, GL_INFO_LOG_LENGTH, &infoLogLength);

		char* pShaderInfoLog = new char[infoLogLength];
		if (pShaderInfoLog) {
			glGetShaderInfoLog(mHandle, infoLogLength, NULL, pShaderInfoLog);
			fLogE("Compilation: %s", pShaderInfoLog);
			delete pShaderInfoLog;
		}
		glDeleteShader(mHandle);
		mHandle = 0;
		fLogF("Shader can not bee compiled");
		std::istringstream lines(mSource);
		std::string line;
		int i = 0;
		while (std::getline(lines, line)) {
			fLogE("[%d] %s", i++, line.c_str());
		}
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
		fLogI("%s\n", infoLog.data());
	}
	fLogI("%s\n", mSource.c_str());
}

void Shader::reload() {
	mHandle = glCreateShader(mType);
	fLogC("Shader creation failed");
	loadSource();
	compile();
}

std::string Shader::getTypeString() {
	switch (mType) {
		case GL_FRAGMENT_SHADER:
			return "GL_FRAGMENT_SHADER";
		case GL_VERTEX_SHADER:
			return "GL_VERTEX_SHADER";
#ifdef FILLWAVE_GLES_3_0
#else
		case GL_GEOMETRY_SHADER:
			return "GL_GEOMETRY_SHADER";
		case GL_TESS_CONTROL_SHADER:
			return "GL_TESS_CONTROL_SHADER";
		case GL_TESS_EVALUATION_SHADER:
			return "GL_TESS_EVALUATION_SHADER";
#endif
		default:
			fLogF("Shader type not recognized: %d", mType);
			return "";
	}
}

} /* core */
} /* fillwave */

std::vector<fillwave::core::Shader*> operator+(
   std::vector<fillwave::core::Shader*> shaders,
   fillwave::core::Shader* shader) {
	shaders.push_back(shader);
	return shaders;
}

