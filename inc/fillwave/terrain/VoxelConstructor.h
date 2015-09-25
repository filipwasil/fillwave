/*
 * Constructor.h
 *
 *  Created on: Dec 18, 2014
 *      Author: Filip Wasil
 */

#ifndef VOXEL_CONSTRUCTOR_H_
#define VOXEL_CONSTRUCTOR_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/OpenGL.h>
#include <fillwave/terrain/TerrainConstructor.h>

namespace fillwave {
namespace terrain {

/*! \class VoxelConstructor
 * \brief Construct Terrain voxel positions.
 */

class VoxelConstructor: public TerrainConstructor {
public:
   VoxelConstructor();
   virtual ~VoxelConstructor();
   virtual GLboolean calculateActiveVoxel(GLfloat x, GLfloat z, GLfloat y) = 0;
   };

} /* terrain */
} /* fillwave */

#endif /* VOXEL_CONSTRUCTOR_H_ */
