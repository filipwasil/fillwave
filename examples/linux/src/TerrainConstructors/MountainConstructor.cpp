/*
 * MountainConstructor.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: filip
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

#include "../../../linux/inc/TerrainConstructors/MountainConstructor.h"

#include <fillwave/Math.h>
#include <fillwave/Log.h>

FLOGINIT("MountainConstructor", FERROR | FFATAL)

namespace flw {
namespace flf {

MountainConstructor::MountainConstructor() {

}

MountainConstructor::~MountainConstructor() {

}

GLboolean MountainConstructor::calculateActiveVoxel(GLfloat x, GLfloat z, GLfloat y) {
  if (y == 0) {
    return GL_TRUE;
  }
  if (calculateHeight(x, z) > y) {
    return GL_TRUE;
  } else {
    return GL_FALSE;
  }
}

inline GLfloat MountainConstructor::calculateHeight(GLfloat x, GLfloat z) {
//   fLogU("X: %f Z: %f Y: %f", x,z,glm::sin(glm::radians(360*x)) * glm::sin(glm::radians(360*z)));
  return glm::sin(glm::radians(360 * x)) * glm::sin(glm::radians(360 * z));
}

} /* framework */
} /* fillwave */
