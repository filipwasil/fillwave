/*
 * Conversion.cpp
 *
 *  Created on: Mar 28, 2014
 *      Author: filip
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

glm::vec3 floatsToGlmVec3(const float* in) {
	return  glm::vec3(in[0], in[1], in[2]);
}

glm::vec4 floatsToGlmVec4(const float* in) {
	return  glm::vec4(in[0], in[1], in[2], in[3]);
}
} /* fillwave */
