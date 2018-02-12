/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
