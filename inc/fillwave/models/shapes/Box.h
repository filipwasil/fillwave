/*
 * Box.h
 *
 *  Created on: 9 Jun 2015
 *      Author: Filip Wasil
 */

#ifndef BOX_H_
#define BOX_H_

#include <fillwave/models/shapes/Quad.h>

namespace fillwave {
namespace models {

class Box: public Shape<core::VertexBasic> {
public:
	Box(GLfloat quadSize = 1.0f)
			: mSize(quadSize), mQuad(quadSize) {
		std::vector<core::VertexBasic> quadVertices = mQuad.getVertices();
		std::vector<glm::vec3> vertVertices;

		mVertices.resize(36);

		/* Back */
		for (int i = 0; i < 6; i++) {
			vertVertices.push_back(
					glm::vec3(quadVertices[i].mPosition[0],
							quadVertices[i].mPosition[1],
							quadVertices[i].mPosition[2] += mSize));
		}

		/* Down */
		for (GLuint i = 0; i < 6; i++) {
			glm::vec3 vec(glm::rotateX(vertVertices[i], glm::radians(90.0f)));
			vertVertices.push_back(vec);
		}

		/* Back */
		for (GLuint i = 0; i < 6; i++) {
			glm::vec3 vec(glm::rotateX(vertVertices[i], glm::radians(180.0f)));
			vertVertices.push_back(vec);
		}

		/* Up */
		for (GLuint i = 0; i < 6; i++) {
			glm::vec3 vec(glm::rotateX(vertVertices[i], glm::radians(270.0f)));
			vertVertices.push_back(vec);
		}

		/* Right */
		for (GLuint i = 0; i < 6; i++) {
			glm::vec3 vec = glm::rotateZ(
					glm::rotateX(vertVertices[i], glm::radians(90.0f)),
					glm::radians(90.0f));
			vertVertices.push_back(vec);
		}

		for (GLuint i = 0; i < 6; i++) {
			glm::vec3 vec = glm::rotateZ(
					glm::rotateX(vertVertices[i], glm::radians(90.0f)),
					glm::radians(-90.0f));
			vertVertices.push_back(vec);
		}

		/* Vertices and Indices */
		for (GLuint i = 0; i < vertVertices.size(); i++) {
			mVertices[i].mPosition[0] = vertVertices[i].x;
			mVertices[i].mPosition[1] = vertVertices[i].y;
			mVertices[i].mPosition[2] = vertVertices[i].z;
			mVertices[i].mPosition[3] = 1.0f;
			mIndices.push_back(i);
		}
	}

	virtual ~Box() = default;

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
