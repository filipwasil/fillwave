/*
 * Conversion.cpp
 *
 *  Created on: Mar 28, 2014
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
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

#include <fillwave/extras/Conversion.h>

namespace fillwave {

glm::mat4 assimpToGlmMat4(aiMatrix4x4 matrix) {
   glm::mat4 out;
   for (int i=0;i<4;i++) {
      for (int j=0;j<4;j++) {
         out[i][j] = matrix[j][i];
      }
   }
   return out;
}

glm::vec3 assimpToGlmVec3(aiVector3D vector) {
   glm::vec3 out;
   for (int i=0;i<3;i++) {
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
