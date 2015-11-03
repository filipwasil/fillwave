/*
 * Sphere.h
 *
 *  Created on: 18 May 2015
 *      Author: Filip Wasil
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include <fillwave/models/shapes/Shape.h>
#include <fillwave/core/buffers/VertexBufferBasic.h>

namespace fillwave {
namespace models {

/*! \class Sphere
 * \brief Shape<core::VertexBasic> encapsulating vertices and indices for triangle drawn UV sphere.
 *
 */

class Sphere: public Shape<core::VertexBasic> {

public:
	Sphere(
			GLfloat radius,
			GLuint rings = 10,
			GLuint sectors = 10,
			glm::vec3 color = glm::vec3(0.0)) {
		float const R = 1. / (float) (rings - 1);
		float const S = 1. / (float) (sectors - 1);
		float r, s;

		mVertices.resize(rings * sectors);

		auto vb = mVertices.begin();

		for (r = 0; r < rings; r++) {
			for (s = 0; s < sectors; s++) {
				float const y = sin(-M_PI_2 + M_PI * r * R);
				float const x = cos(2 * M_PI * s * S) * sin( M_PI * r * R);
				float const z = sin(2 * M_PI * s * S) * sin( M_PI * r * R);

				(*vb).mTextureUV[0] = s * S;
				(*vb).mTextureUV[1] = r * R;

				(*vb).mPosition[0] = x * radius;
				(*vb).mPosition[1] = y * radius;
				(*vb).mPosition[2] = z * radius;
				(*vb).mPosition[3] = 1.0;

				(*vb).mNormal[0] = x;
				(*vb).mNormal[1] = y;
				(*vb).mNormal[2] = z;

				(*vb).mColor[0] = color.x;
				(*vb).mColor[1] = color.y;
				(*vb).mColor[2] = color.z;
				vb++;
			}
		}

		mIndices.resize((rings - 1) * sectors * 6 - 1);
		auto i = mIndices.begin();
		for (r = 0; r < rings - 1; r++) {
			for (s = 0; s < sectors; s++) {
				if (r == rings - 1 || s == sectors - 1) {
					break;
				}

				*i++ = r * sectors + (s + 1);
				*i++ = r * sectors + s;
				*i++ = (r + 1) * sectors + (s + 1);
				*i++ = (r + 1) * sectors + s;
				*i++ = (r + 1) * sectors + (s + 1);
				*i++ = r * sectors + s;
			}
		}
	}

	~Sphere() = default;
};

} /* models */
} /* fillwave */

#endif /* SPHERE_H_ */
