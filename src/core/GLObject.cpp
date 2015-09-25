/*
 * GLObject.cpp
 *
 *  Created on: 22 May 2015
 *      Author: Filip Wasil
 */

#include <fillwave/core/GLObject.h>

namespace fillwave {
namespace core {

GLObject::GLObject(GLsizei howMany)
:mHowMany(howMany),
 mHandles(new GLuint[howMany]) {

}

GLObject::~GLObject() {
   delete mHandles;
}

GLuint GLObject::getHandle(GLuint id) {
   return mHandles[id];
}

} /* core */
} /* fillwave */
