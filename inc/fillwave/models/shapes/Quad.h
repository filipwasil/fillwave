/*
 * Quad.h
 *
 *  Created on: May 25, 2015
 *      Author: Filip Wasil
 */

#ifndef SRC_MODELS_SHAPES_QUAD_H_
#define SRC_MODELS_SHAPES_QUAD_H_

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

/*! \class Quad
 * \brief Shape encapsulating vertices and indices for triangle drawn quad.
 *
 */

class Quad: public Shape<core::VertexBasic>  {
public:
   Quad(GLfloat size = 1.0f);
   virtual ~Quad();
};

} /* models */
} /* fillwave */

#endif /* SRC_MODELS_SHAPES_QUAD_H_ */
