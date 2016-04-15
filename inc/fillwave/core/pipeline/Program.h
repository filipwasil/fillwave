/*
 * Program.h
 *
 *  Created on: 27 Mar 2014
 *      Author: Filip Wasil
 */

#ifndef GLPROGRAM_H_
#define GLPROGRAM_H_

#include <fillwave/core/pipeline/Uniform.h>
#include <fillwave/core/pipeline/Shader.h>
#include <fillwave/core/pipeline/UniformBuffer.h>
#include <memory>
#include <iostream>
#include <string>

#define FILLWAVE_LIGHTS_BINDING_POINT_NAME "uSpotLightsUBO"

class Attribute;

namespace fillwave {
namespace core {

/*! \class Program
 * \brief Single GLSL program object.
 */
class Program {
 public:
	Program(const std::vector<core::Shader*>& shaders,
	        GLboolean skipLinking = GL_FALSE);

	virtual ~Program();

	void link();

	/* Shaders */
	void attach(core::Shader* shader);
	void detach(core::Shader* shader);

	void use() const;

	static void useProgram(GLuint handle);
	static void disusePrograms();

	/* Uniforms */
	GLboolean checkUniform(const std::string& name);

	void uniformPush(std::string name, GLint data);
	void uniformPush(std::string name, GLint* data, GLint count);
	void uniformPush(std::string name, GLfloat data);
	void uniformPush(std::string name, GLfloat* data, GLint count);
	void uniformPush(std::string name, glm::mat3 data);
	void uniformPush(std::string name, glm::mat4 data);
	void uniformPush(std::string name, glm::mat4* data, GLuint size);
	void uniformPush(std::string name, glm::vec2 data);
	void uniformPush(std::string name, glm::vec3 data);
	void uniformPush(std::string name, glm::vec3* data, GLuint size);
	void uniformPush(std::string name, glm::vec4 data);

	/* Uniform blocks */
	GLint getUniformLocation(std::string name);
	void getUniformBlock(std::string name, GLuint bindingPoint);
	GLuint getHandle() const;
	void uniformBlockPush(std::string name, GLfloat* data);

	void reload();
	void log() const;

 private:
	GLuint mHandle;
	std::vector<Uniform> mUniforms;
	std::vector<puUniformBuffer> mUnifromBuffers;
	GLboolean mDelayedLinking;
	std::vector<core::Shader*> mShaders;
	void getUniforms();
};

} /* core */
static core::Program* buildProgram( //xxx this should not be public
   const std::vector<core::Shader*>& shaders,
   GLboolean skipLinking = GL_FALSE) {
	return new core::Program(shaders, skipLinking);
}
} /* fillwave */

#endif /* GLPROGRAM_H_ */
