/*
 * VertexBufferPosition.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: Filip Wasil
 */

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2015] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * filip.wasil@gmail.com
 *
 */

#include <fillwave/core/buffers/VertexBufferPosition.h>

FLOGINIT("VertexBufferPosition", FERROR | FFATAL)

namespace fillwave {
namespace core {

VertexBufferPosition::VertexBufferPosition(
		models::Shape<VertexPosition>& shape,
		GLuint dataStoreModification)
		: VertexBuffer<VertexPosition>(shape, dataStoreModification) {

}

VertexBufferPosition::VertexBufferPosition(
		std::vector<VertexPosition>& vertices,
		GLuint dataStoreModification)
		: VertexBuffer<VertexPosition>(vertices, dataStoreModification) {

}

VertexBufferPosition::~VertexBufferPosition() {

}

void VertexBufferPosition::log() {
	for (auto it : mDataVertices) {
		FLOG_INFO("Vertex written: %f %f %f %f", it.mPosition[0], it.mPosition[1],
				it.mPosition[2], it.mPosition[3]);
	}
}

} /* core */
} /* fillwave*/

