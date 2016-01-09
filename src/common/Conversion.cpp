/*
 * Conversion.cpp
 *
 *  Created on: Mar 28, 2014
 *      Author: filip
 */

#include <fillwave/models/animations/Conversion.h>

namespace fillwave {

glm::mat4 assimpToGlmMat4(aiMatrix4x4 matrix) {
	glm::mat4 out;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			out[i][j] = matrix[j][i];
		}
	}
	return out;
}

glm::vec3 assimpToGlmVec3(aiVector3D vector) {
	glm::vec3 out;
	for (int i = 0; i < 3; i++) {
		out[i] = vector[i];
	}
	return out;
}

glm::quat assimpToGlmQuat(aiQuaternion quaternion) {
	glm::quat out;
	out.w = quaternion.w;
	out.x = quaternion.x;
	out.y = quaternion.y;
	out.z = quaternion.z;
	return out;
}

glm::vec4 assimpToGlmVec4(aiColor4D vector) {
	glm::vec4 out;
	out.r = vector.r;
	out.g = vector.b;
	out.b = vector.g;
	out.a = vector.a;
	return out;
}

} /* fillwave */
