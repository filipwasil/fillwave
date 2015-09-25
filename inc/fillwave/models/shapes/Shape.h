/*
 * Shape.h
 *
 *  Created on: 18 May 2015
 *      Author: Filip Wasil
 */

#ifndef SHAPE_H_
#define SHAPE_H_

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
#include <vector>

namespace fillwave {
namespace models {

/*! \class Shape
 * \brief Base class for every shape. Specialized with Vertex data structure.
 *
 */

template<class T>
class Shape {
public:
	Shape() {

	}

	virtual ~Shape() {

	}

	std::vector<T> getVertices() {
		return mVertices;
	}

	GLuint getVerticesSize() {
		return mVertices.size();
	}

	std::vector<GLuint> getIndices() {
		return mIndices;
	}

	GLuint getIndicesSize() {
		return mIndices.size();
	}

protected:
	std::vector<T> mVertices;
	std::vector<GLuint> mIndices;
};

} /* models */
} /* fillwave */
#endif /* SHAPE_H_ */
