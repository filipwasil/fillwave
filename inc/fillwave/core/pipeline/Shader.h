/*
 * Shader.h
 *
 *  Created on: 28 Mar 2013
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

#pragma once

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
