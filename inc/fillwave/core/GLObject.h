/*
 * GLObject.h
 *
 *  Created on: 22 May 2015
 *      Author: Filip Wasil
 */

#ifndef GLOBJECT_H_
#define GLOBJECT_H_

#include <fillwave/OpenGL.h>

namespace fillwave {
namespace core {

/*! \class GLObject
 * \brief Base class for all OpenGL objects not related to pipeline.
 */

class GLObject {
  public:
	GLObject(GLsizei howMany);

	virtual ~GLObject();

	GLuint getHandle(GLuint id = 0);

	virtual void reload() = 0;

  protected:
	GLsizei mHowMany;
	GLuint* mHandles;
};

} /* core */
} /* fillwave */

#endif /* GLOBJECT_H_ */
