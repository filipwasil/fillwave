/*
 * Sphere.h
 *
 *  Created on: 18 May 2015
 *      Author: Filip Wasil
 */

#ifndef SPHERE_H_
#define SPHERE_H_

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

#include <fillwave/models/shapes/Shape.h>
#include <fillwave/core/buffers/VertexBufferBasic.h>

namespace fillwave {
namespace models {

/*! \class Sphere
 * \brief Shape<core::VertexBasic> encapsulating vertices and indices for triangle drawn UV sphere.
 *
 */

class Sphere : public Shape<core::VertexBasic> {

public:
   Sphere(GLfloat radius,
          GLuint rings = 10,
          GLuint sectors = 10,
          glm::vec3 color = glm::vec3(0.0));

   ~Sphere();
};


} /* models */
} /* fillwave */

#endif /* SPHERE_H_ */
