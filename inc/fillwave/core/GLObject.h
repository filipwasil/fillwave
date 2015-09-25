/*
 * GLObject.h
 *
 *  Created on: 22 May 2015
 *      Author: Filip Wasil
 */

#ifndef GLOBJECT_H_
#define GLOBJECT_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

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
