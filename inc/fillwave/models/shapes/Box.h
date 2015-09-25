/*
 * Box.h
 *
 *  Created on: 9 Jun 2015
 *      Author: Filip Wasil
 */

#ifndef BOX_H_
#define BOX_H_

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
#include <fillwave/models/shapes/Quad.h>

namespace fillwave {
namespace models {

class Box: public Shape<core::VertexBasic> {
public:
   Box(GLfloat quadSize = 1.0f);

   virtual ~Box();

   void generateVertices();

   void generateSide();

   void generateIndices();

private:
   GLfloat mSize;
   Quad mQuad;
};

} /* models */
} /* fillwave */
#endif /* BOX_H_ */
