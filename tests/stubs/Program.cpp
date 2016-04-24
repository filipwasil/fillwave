/*
 * Program.cpp
 *
 *  Created on: Jan 17, 2016
 *      Author: filip
 */

#include <fillwave/core/pipeline/Program.h>
#include <fillwave/Log.h>

FLOGINIT("Program", FERROR | FFATAL | FINFO | FDEBUG)

using namespace std;

namespace fillwave {
namespace core {

Program::Program(const std::vector<core::Shader*>& shaders, GLboolean skipLinking)
		: mDelayedLinking(skipLinking), mShaders(shaders) {
	reload();
}

Program::~Program() {
	for (auto& it : mShaders) {
		detach(it);
	}
}

void Program::attach(core::Shader* /*shader*/) {

}

void Program::detach(core::Shader* /*shader*/) {

}

GLuint Program::getHandle() const {
	return mHandle;
}

void Program::link() {

}

void Program::disusePrograms() {

}

void Program::useProgram(GLuint /*handle*/) {

}

void Program::use() const {

}

void Program::uniformPush(string /*name*/, GLint /*data*/) {

}

void Program::uniformPush(string /*name*/, GLint* /*data*/, GLint /*count*/) {

}

void Program::uniformPush(string /*name*/, GLfloat /*data*/) {

}

void Program::uniformPush(string /*name*/, GLfloat* /*data*/, GLint /*count*/) {

}

void Program::uniformPush(string /*name*/, glm::mat3 /*data*/) {

}

void Program::uniformPush(string /*name*/, glm::mat4 /*data*/) {

}

void Program::uniformPush(string /*name*/, glm::mat4* /*data*/, GLuint /*size*/) {

}

void Program::uniformPush(string /*name*/, glm::vec2 /*data*/) {

}

void Program::uniformPush(string /*name*/, glm::vec3 /*data*/) {

}

void Program::uniformPush(string /*name*/, glm::vec3* /*data*/, GLuint /*size*/) {

}

void Program::uniformPush(string /*name*/, glm::vec4 /*data*/) {

}

inline void Program::getUniforms() {

}

void Program::getUniformBlock(std::string /*name*/, GLuint /*bindingPoint*/) {

}

void Program::uniformBlockPush(std::string /*name*/, GLfloat* /*data*/) {
}

void Program::log() const {
}

void Program::reload() {
}

	core::Program* buildProgram(
			const std::vector<core::Shader*>& shaders,
			GLboolean skipLinking) {
		return nullptr;
	}

}
}


