/*
 * MountainConstructor.h
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

#ifndef MOUNTAINCONSTRUCTOR_H_
#define MOUNTAINCONSTRUCTOR_H_

#include <flw/flf/models/terrain/VoxelConstructor.h>

namespace flw {
namespace flf {

/*! \class MountainConstructor
 * \brief Implements VoxelConstructor and QuadConstructor to build an example terrain.
 */

class MountainConstructor : public VoxelConstructor {
public:
  MountainConstructor();

  virtual ~MountainConstructor();

  GLboolean calculateActiveVoxel(GLfloat x, GLfloat z, GLfloat y);

  GLfloat calculateHeight(GLfloat x, GLfloat z) const;
};

} /* framework */
} /* fillwave */

#endif /* MOUNTAINCONSTRUCTOR_H_ */
