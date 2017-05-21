#include <scene/terrain/MountainConstructor.h>
#include <fillwave/Math.h>

namespace flw {
namespace flf {

GLboolean MountainConstructor::calculateActiveVoxel(GLfloat x, GLfloat z,
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

GLfloat MountainConstructor::calculateHeight(GLfloat x, GLfloat z) {
	return glm::sin(glm::radians(360 * x)) * glm::sin(glm::radians(360 * z));
}

} /* framework */
} /* fillwave */
