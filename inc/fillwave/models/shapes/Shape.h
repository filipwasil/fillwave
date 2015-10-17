/*
 * Shape.h
 *
 *  Created on: 18 May 2015
 *      Author: Filip Wasil
 */

#ifndef SHAPE_H_
#define SHAPE_H_


#include <fillwave/OpenGL.h>
#include <fillwave/Math.h>
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
