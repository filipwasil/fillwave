/*
 * Conversion.cpp
 *
 *  Created on: Mar 28, 2014
 *      Author: filip
 *
 * Copyright (c) 2017, Fillwave developers
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

namespace flw {

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

glm::mat4 assimpToGlmMat4(aiMatrix4x4 matrix) {
  glm::mat4 out;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      out[i][j] = matrix[j][i];
    }
  }
  return out;
}

glm::vec3 assimpToGlmVec3(aiVector3D vector) {
  return glm::vec3(vector.x, vector.y, vector.z);
}

glm::quat assimpToGlmQuat(aiQuaternion quaternion) {
  return glm::quat(quaternion.w, quaternion.x, quaternion.y, quaternion.z);
}

glm::vec4 assimpToGlmVec4(aiColor4D vector) {
  return glm::vec4(vector.r, vector.g, vector.b, vector.a);
}

#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

glm::vec3 floatsToGlmVec3(const float *in) {
  return glm::vec3(in[0], in[1], in[2]);
}

glm::vec4 floatsToGlmVec4(const float *in) {
  return glm::vec4(in[0], in[1], in[2], in[3]);
}

} /* flw */
