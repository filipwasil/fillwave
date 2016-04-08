/*
 * SphereSkybox.h
 *
 *  Created on: 18 May 2015
 *      Author: Filip Wasil
 */

#ifndef SPHERESKYBOX_H_
#define SPHERESKYBOX_H_

#include <fillwave/core/buffers/VertexBufferPosition.h>
#include <fillwave/models/shapes/Shape.h>

namespace fillwave {
class Engine;
namespace framework {

/*! \class SphereSkybox
 * \brief Shape<core::VertexPosition> encapsulating vertices and indices for triangle drawn UV sphere.
 *
 */

class SphereSkybox: public Shape<core::VertexPosition> {
public:
	SphereSkybox(GLfloat radius, GLuint rings, GLuint sectors) {
		float const R = 1.f / (float) (rings - 1);
		float const S = 1.f / (float) (sectors - 1);
		GLuint r, s;

		mVertices.resize(rings * sectors);

		auto vb = mVertices.begin();

		for (r = 0; r < rings; r++) {
			for (s = 0; s < sectors; s++) {
				float const y = sin(-F_PI_2 + F_PI * r * R);
				float const x = cos(2 * F_PI * s * S) * sin(F_PI * r * R);
				float const z = sin(2 * F_PI * s * S) * sin(F_PI * r * R);

				(*vb).mPosition[0] = x * radius * mScale;
				(*vb).mPosition[1] = y * radius * mScale;
				(*vb).mPosition[2] = z * radius * mScale;
				(*vb).mPosition[3] = 1.0;

				vb++;
			}
		}

		mIndices.resize(rings * sectors * 6);
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

	virtual ~SphereSkybox() = default;

private:
	const GLfloat mScale = 100.0;
};

} /* framework */
} /* fillwave */

#endif /* SPHERESKYBOX_H_ */
