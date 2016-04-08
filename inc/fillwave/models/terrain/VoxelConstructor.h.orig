/*
 * Constructor.h
 *
 *  Created on: Dec 18, 2014
 *      Author: Filip Wasil
 */

#ifndef VOXEL_CONSTRUCTOR_H_
#define VOXEL_CONSTRUCTOR_H_

#include <fillwave/OpenGL.h>
#include <fillwave/models/terrain/TerrainConstructor.h>

namespace fillwave {
namespace framework {

/*! \class VoxelConstructor
 * \brief Construct Terrain voxel positions.
 */

class VoxelConstructor: public TerrainConstructor {
public:
	VoxelConstructor() = default;
	virtual ~VoxelConstructor() = default;
	virtual GLboolean calculateActiveVoxel(GLfloat x, GLfloat z, GLfloat y) = 0;
};

} /* framework */
} /* fillwave */

#endif /* VOXEL_CONSTRUCTOR_H_ */
