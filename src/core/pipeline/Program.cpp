/*
 * Program.cpp
 *
 *  Created on: 3 Oct 2013
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


#include <fillwave/core/pipeline/Program.h>
#include <fillwave/core/pipeline/Attribute.h>

#include <fillwave/Log.h>

FLOGINIT("Program", FERROR | FFATAL | FINFO | FDEBUG)

using namespace std;

namespace fillwave {
namespace core {

Program::Program(const std::vector<core::Shader*>& shaders,
                 GLboolean skipLinking) :
	mDelayedLinking(skipLinking), mShaders(shaders) {
	reload();
}

Program::~Program() {
	FLOG_DEBUG("Delete program", NULL);
	for (auto& it : mShaders) {
		detach(it);
	}
	glDeleteProgram(mHandle);
	FLOG_CHECK("Delete program");
}

void Program::attach(core::Shader* shader) {
	if (mHandle) {
		glAttachShader(mHandle, shader->getHandle());
		FLOG_CHECK("attach shader %d to program %d", shader->getHandle(),
		           mHandle);
	}
}

void Program::detach(core::Shader* shader) {
	if (mHandle) {
		glDetachShader(mHandle, shader->getHandle());
		FLOG_CHECK("detach shader");
	}
}

GLuint Program::getHandle() const {
	return mHandle;
}

void Program::link() {
	glLinkProgram(mHandle);

	GLint status = 0;
	glGetProgramiv(mHandle, GL_LINK_STATUS, &status);

	if (!status) {
		GLint infoLogLength = 0;
		glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength) {
			if (GLchar* pInfoLog = new GLchar[infoLogLength]) {
				glGetProgramInfoLog(mHandle, infoLogLength, nullptr, pInfoLog);
				FLOG_FATAL("linking : %s", pInfoLog);
				delete pInfoLog;
			}
		}
		mHandle = 0;
	}

	use();
	getUniforms();
	getUniformBlock(FILLWAVE_LIGHTS_BINDING_POINT_NAME,
	                FILLWAVE_LIGHTS_BINDING_POINT);
	disusePrograms();
}

void Program::disusePrograms() {
	glUseProgram(0);
	FLOG_CHECK("disuse programs");
}

void Program::useProgram(GLuint handle) {
	glUseProgram(handle);
	FLOG_CHECK("disuse programs");
}

void Program::use() const {
	glUseProgram(mHandle);
	FLOG_CHECK("use");
}

void Program::uniformPush(string name, GLint data) {
	for (auto& it : mUniforms) {
		if (it.isName(name)) {
			it.push(data);
			return;
		}
	}
	FLOG_ERROR("Can not find \"int %s\" uniform name in program", name.c_str());
}

void Program::uniformPush(string name, GLint* data, GLint count) {
	for (auto& it : mUniforms) {
		if (it.isName(name)) {
			it.push(data, count);
			return;
		}
	}
	FLOG_ERROR("Can not find \"int %s\" uniform name in program", name.c_str());
}

void Program::uniformPush(string name, GLfloat data) {
	for (auto& it : mUniforms) {
		if (it.isName(name)) {
			it.push(data);
			return;
		}
	}
	FLOG_ERROR("Can not find \"float %s\" uniform name in program",
	           name.c_str());
}

void Program::uniformPush(string name, GLfloat* data, GLint count) {
	for (auto& it : mUniforms) {
		if (it.isName(name)) {
			it.push(data, count);
			return;
		}
	}
	FLOG_ERROR("Can not find \"float %s\" uniform name in program",
	           name.c_str());
}

void Program::uniformPush(string name, glm::mat3 data) {
	for (auto& it : mUniforms) {
		if (it.isName(name)) {
			it.push(data);
			return;
		}
	}
	FLOG_ERROR("Can not find \"mat3 %s\" uniform name in program", name.c_str());
}

void Program::uniformPush(string name, glm::mat4 data) {
	for (auto& it : mUniforms) {
		if (it.isName(name)) {
			it.push(data);
			return;
		}
	}
	FLOG_ERROR("Can not find \"mat4 %s\" uniform name in program", name.c_str());
}

void Program::uniformPush(string name, glm::mat4* data, GLuint size) {
	for (auto& it : mUniforms) {
		if (it.isName(name)) {
			it.push(data, size);
			return;
		}
	}
	FLOG_ERROR("Can not find \"mat4 %s\" uniform name in program", name.c_str());
}

void Program::uniformPush(string name, glm::vec2 data) {
	for (auto& it : mUniforms) {
		if (it.isName(name)) {
			it.push(data);
			return;
		}
	}
	FLOG_ERROR("Can not find \"glm::vec2 %s\" uniform name in program",
	           name.c_str());
}

void Program::uniformPush(string name, glm::vec3 data) {
	for (auto& it : mUniforms) {
		if (it.isName(name)) {
			it.push(data);
			return;
		}
	}
	FLOG_ERROR("Can not find \"glm::vec3 %s\" uniform name in program",
	           name.c_str());
}

void Program::uniformPush(string name, glm::vec3* data, GLuint size) {
	for (auto& it : mUniforms) {
		if (it.isName(name)) {
			it.push(data, size);
			return;
		}
	}
	FLOG_ERROR("Can not find %d \"vec3 %s\" uniforms name in program", size,
	           name.c_str());
}

void Program::uniformPush(string name, glm::vec4 data) {
	for (auto& it : mUniforms) {
		if (it.isName(name)) {
			it.push(data);
			return;
		}
	}
	FLOG_ERROR("Can not find \"glm::vec4 %s\" uniform name in program",
	           name.c_str());
}

inline void Program::getUniforms() {
	if (mUniforms.empty()) {
		GLint howMany = -1;
		glGetProgramiv(mHandle, GL_ACTIVE_UNIFORMS, &howMany);
		for (GLint i = 0; i < howMany; ++i) {
			GLint name_len = -1, num = -1;
			GLenum type = GL_ZERO;
			char name[100];
			glGetActiveUniform(mHandle, GLuint(i), sizeof(name) - 1, &name_len,
			                   &num, &type, name);
			name[name_len] = 0;
			GLint location = glGetUniformLocation(mHandle, name);
			FLOG_DEBUG("Uniform name=%s, location=%d, type=%d, num=%d", name,
			           location, type, num);
			mUniforms.push_back(Uniform(name, type, num, location));
		}
	}
}

GLint Program::getUniformLocation(std::string name) {
	for (auto& it : mUniforms) {
		if (it.isName(name)) {
			return it.getLocation();
		}
	}
	FLOG_DEBUG("Can not find uniform %s in program", name.c_str());
	return FILLWAVE_UNIFORM_NOT_FOUND;
}

void Program::getUniformBlock(std::string name, GLuint bindingPoint) {
	GLint howMany = -1;
	GLint uniformBlockSize = 0;
	glGetProgramiv(mHandle, GL_ACTIVE_UNIFORM_BLOCKS, &howMany);
	for (GLint i = 0; i < howMany; ++i) {
		GLint name_len = -1;
		std::vector<char> nameFromProgram(100);
		glGetActiveUniformBlockName(mHandle, GLuint(i),
		                            sizeof(nameFromProgram) - 1, &name_len, nameFromProgram.data());
		glGetActiveUniformBlockiv(mHandle, GLuint(i),
		                          GL_UNIFORM_BLOCK_DATA_SIZE, &uniformBlockSize);
		nameFromProgram[name_len] = 0;
		if (std::string(nameFromProgram.data()) == name) {
			FLOG_DEBUG("Uniform block name=%s, index=%d, size=%d ",
			           std::string(name).c_str(), GLuint(i), uniformBlockSize);
			GLuint blockIndex = glGetUniformBlockIndex(mHandle,
			                    nameFromProgram.data());
			glUniformBlockBinding(mHandle, blockIndex, bindingPoint);
			mUnifromBuffers.push_back(
			   std::make_unique<UniformBuffer>(std::string(name), blockIndex,
			                                   uniformBlockSize, bindingPoint,
			                                   GL_DYNAMIC_DRAW));
		}
	}
}

void Program::uniformBlockPush(std::string name, GLfloat* data) {
	for (auto& it : mUnifromBuffers) {
		if (it->getName() == name) {
			it->push(data);
			return;
		}
	}
	FLOG_ERROR("Uniform buffer %s not found", name.c_str());
}

void Program::log() const {
	GLint infologLength = 0;
	GLint value;
	glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &value);
	std::vector<GLchar> infoLog(value);
	FLOG_INFO("Shaders\n %lu", mShaders.size());
	if (glIsProgram(mHandle)) {
		FLOG_INFO("Program handle %d is valid", mHandle);
	} else {
		FLOG_INFO("Program handle %d is not valid", mHandle);
	}
	glGetProgramInfoLog(mHandle, value, &infologLength, infoLog.data());
	FLOG_INFO("INFOR LOG: %s", infoLog.data());
	glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &value);
	FLOG_INFO("GL_INFO_LOG_LENGTH: %d", value);
	glGetProgramiv(mHandle, GL_VALIDATE_STATUS, &value);
	FLOG_INFO("GL_VALIDATE_STATUS: %d", value);
	glGetProgramiv(mHandle, GL_ATTACHED_SHADERS, &value);
	FLOG_INFO("GL_ATTACHED_SHADERS: %d", value);
	glGetProgramiv(mHandle, GL_ACTIVE_ATTRIBUTES, &value);
	FLOG_INFO("GL_ACTIVE_ATTRIBUTES: %d", value);
	glGetProgramiv(mHandle, GL_ACTIVE_UNIFORMS, &value);
	FLOG_INFO("GL_ACTIVE_UNIFORMS: %d", value);
	glGetProgramiv(mHandle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &value);
	FLOG_INFO("GL_ACTIVE_ATTRIBUTE_MAX_LENGTH: %d", value);
	glGetProgramiv(mHandle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &value);
	FLOG_INFO("GL_ACTIVE_UNIFORM_MAX_LENGTH: %d", value);

	FLOG_INFO("Uniforms:\n %lu", mUniforms.size());
	for (auto& it : mUniforms) {
		it.log();
	}
	for (auto& it : mShaders) {
		FLOG_INFO("Shader:\n", NULL);
		it->log();
	}
}

void Program::reload() {
	mHandle = glCreateProgram();
	FLOG_CHECK("Program creation failed");
	for (auto it : mShaders) {
		attach(it);
		FLOG_CHECK("Failed to attach shader of type %s",
		           it->getTypeString().c_str());
	}
	if (!mDelayedLinking) {
		link();
	} else {
		FLOG_DEBUG("Program linking has be done manually\n", NULL);
	}
	FLOG_CHECK("Program linking failed");
}
} /* core */
core::Program* buildProgram(
   const std::vector<core::Shader*>& shaders,
   GLboolean skipLinking) {
	return new core::Program(shaders, skipLinking);
}
} /* fillwave */
