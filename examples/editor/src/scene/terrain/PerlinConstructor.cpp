#include <fillwave/Math.h>
#include <scene/terrain/PerlinConstructor.h>
#include <glm/gtc/noise.hpp>

namespace flw {
namespace flf {

PerlinConstructor::PerlinConstructor() {
//	noise::module::Perlin mPerlin;
}

PerlinConstructor::~PerlinConstructor() {

}

GLboolean PerlinConstructor::calculateActiveVoxel(GLfloat x, GLfloat z,
      GLfloat y) {
	if ( y == 0 ) {
		return GL_TRUE;
	}
	if (calculateHeight(x, z) > y) {
		return GL_TRUE;
	} else {
		return GL_FALSE;
	}
}

inline GLfloat PerlinConstructor::calculateHeight(GLfloat x, GLfloat z) {
	return glm::perlin(glm::vec2(x, z));
}

} /* flf */
} /* flw */
