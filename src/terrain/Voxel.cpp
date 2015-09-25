/*
 * Voxel.cpp
 *
 *  Created on: Dec 1, 2014
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
 * fillwave@gmail.com
 *
 */

#include <fillwave/terrain/Voxel.h>

namespace fillwave {
namespace terrain {

Voxel::Voxel()
:mType(0),
 mActive(GL_TRUE) {
}

Voxel::~Voxel() {

}

GLboolean Voxel::isActive() {
   return mActive;
}
void Voxel::setActive(GLboolean active) {
   mActive = active;
}

void Voxel::setType(GLint type) {
   mType = type;
}

} /* core */
} /* fillwave */
