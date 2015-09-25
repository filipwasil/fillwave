/*
 * IndexBufferBasic.h
 *
 *  Created on: 17 May, 2014
 *      Author: Filip Wasil
 */

#ifndef INDEXBUFFERBASIC_H_
#define INDEXBUFFERBASIC_H_

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

#include <fillwave/core/buffers/IndexBuffer.h>
#include <fillwave/models/shapes/Shape.h>
#include <fillwave/Assets.h>

namespace fillwave {
namespace core {

/*! \class IndexBufferBasic
 * \brief IndexBuffer for regular usage.
 */

class IndexBufferBasic: public IndexBuffer {
public:
	IndexBufferBasic(std::vector<GLuint>& data, GLuint dataStoreModification =
			GL_STATIC_DRAW);

	IndexBufferBasic(const fMesh* shape, GLuint dataStoreModification =
			GL_STATIC_DRAW);

	template<class T>
	IndexBufferBasic(models::Shape<T>& shape, GLuint dataStoreModification =
			GL_STATIC_DRAW)
			: IndexBuffer(shape.getIndicesSize(), dataStoreModification) {
		mDataIndices = shape.getIndices();
		mData = mDataIndices.data();
	}

	virtual ~IndexBufferBasic();
	void loadElement(GLuint element);
};

} /* core */
typedef std::shared_ptr<core::IndexBufferBasic> pIndexBufferBasic;
} /* fillwave */

#endif /* INDEXBUFFERBASIC_H_ */
