/*
 * BoxOcclusion.h
 *
 *  Created on: 10 Jun 2015
 *      Author: Filip Wasil
 */

#ifndef BOXOCCLUSION_H_
#define BOXOCCLUSION_H_

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
#include <fillwave/core/buffers/VertexBufferPosition.h>
#include <fillwave/models/shapes/Quad.h>

namespace fillwave {
namespace models {

class BoxOcclusion: public Shape<core::VertexPosition> {
public:
	BoxOcclusion(GLfloat quadSize = 1.0f);
	virtual ~BoxOcclusion();

private:
	GLfloat mSize;
	Quad mQuad;
};

} /* models */
} /* fillwave */

#endif /* BOXOCCLUSION_H_ */
