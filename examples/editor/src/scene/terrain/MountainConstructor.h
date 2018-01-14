#pragma once

#include <fillwave/models/terrain/VoxelConstructor.h>

namespace flw {
namespace flf {

/*! \class MountainConstructor
 * \brief Implements VoxelConstructor and QuadConstructor to build an example terrain.
 */

class MountainConstructor: public VoxelConstructor {
 public:
	MountainConstructor() = default;
	virtual ~MountainConstructor() = default;
	GLboolean calculateActiveVoxel(GLfloat x, GLfloat z, GLfloat y) override;
	GLfloat calculateHeight(GLfloat x, GLfloat z) override;
};

} /* framework */
} /* fillwave */
