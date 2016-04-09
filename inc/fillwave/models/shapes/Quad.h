/*
 * Quad.h
 *
 *  Created on: May 25, 2015
 *      Author: Filip Wasil
 */

#ifndef SRC_MODELS_SHAPES_QUAD_H_
#define SRC_MODELS_SHAPES_QUAD_H_

#include <fillwave/core/buffers/VertexBufferBasic.h>
#include <fillwave/models/shapes/Shape.h>

namespace fillwave {
namespace framework {

/*! \class Quad
 * \brief Shape encapsulating vertices and indices for triangle drawn quad.
 */

class Quad: public Shape<core::VertexBasic> {
 public:
	Quad(GLfloat size = 1.0f) {

		mVertices.resize(6);

		core::VertexBasic position[6] = { { { -size, -size, 0.0, 1.0 }, {
					0.0,
					0.0,
					0.0,
					1.0
				}, { 0.0, 0.0, -1.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 0.0 }, { 0 }, {
					0.0
				}
			}, { { size, -size, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, {
					0.0,
					0.0,
					-1.0
				}, { 1.0, 0.0, 0.0 }, { 1.0, 0.0 }, { 0 }, { 0.0 }
			}, {
				{ size, size, 0.0, 1.0 },
				{ 0.0, 0.0, 0.0, 1.0 },
				{ 0.0, 0.0, -1.0 },
				{ 1.0, 0.0, 0.0 },
				{ 1.0, 1.0 },
				{ 0 },
				{ 0.0 }
			}, { { size, size, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, {
					0.0,
					0.0,
					-1.0
				}, { 1.0, 0.0, 0.0 }, { 1.0, 1.0 }, { 0 }, { 0.0 }
			}, {
				{ -size, size, 0.0, 1.0 },
				{ 0.0, 0.0, 0.0, 1.0 },
				{ 0.0, 0.0, -1.0 },
				{ 1.0, 0.0, 0.0 },
				{ 0.0, 1.0 },
				{ 0 },
				{ 0.0 }
			}, { { -size, -size, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, {
					0.0,
					0.0,
					-1.0
				}, { 1.0, 0.0, 0.0 }, { 0.0, 0.0 }, { 0 }, { 0.0 }
			},
		};

		for (size_t i = 0; i < mVertices.size(); i++) {
			mVertices[i] = position[i];
			mIndices.push_back(i);
		}
	}
	virtual ~Quad() = default;
};

} /* framework */
} /* fillwave */

#endif /* SRC_MODELS_SHAPES_QUAD_H_ */
