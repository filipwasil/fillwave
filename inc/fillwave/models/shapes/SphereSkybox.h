/*
 * SphereSkybox.h
 *
 *  Created on: 18 May 2015
 *      Author: Filip Wasil
 */

#ifndef SPHERESKYBOX_H_
#define SPHERESKYBOX_H_

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

#include <fillwave/core/buffers/VertexBufferPosition.h>
#include <fillwave/models/shapes/Shape.h>

namespace fillwave {
class Engine;
namespace models {

/*! \class SphereSkybox
 * \brief Shape<core::VertexPosition> encapsulating vertices and indices for triangle drawn UV sphere.
 *
 */

class SphereSkybox: public Shape<core::VertexPosition> {
public:
	SphereSkybox(GLfloat radius, GLuint rings, GLuint sectors);

	virtual ~SphereSkybox();

private:
	const GLfloat mScale = 100.0;
};

} /* models */
} /* fillwave */

#endif /* SPHERESKYBOX_H_ */
