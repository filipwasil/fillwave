/*
 * VertexArray.h
 *
 *  Created on: 4 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef VERTEX_ARRAY_H_
#define VERTEX_ARRAY_H_

#include <fillwave/core/GLObject.h>
#include <memory>

namespace fillwave {
namespace core {

/*! \class VertexArray
 * \brief VertexArrayObject - VAO
 */

class VertexArray: public GLObject {
public:
	VertexArray(GLuint howMany = 1);

	virtual ~VertexArray();

	void bind(GLuint id = 0);

	void unbind();

	void reload();
};

} /* buffer */
typedef std::shared_ptr<core::VertexArray> pVertexArray;
typedef std::weak_ptr<core::VertexArray> pwVertexArray;
} /* fillwave */

#endif /* ARRAY_H_ */
