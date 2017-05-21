#pragma once

#include <fillwave/models/terrain/VoxelConstructor.h>

namespace flw {
namespace flf {

/*! \class PerlinConstructor
 * \brief Implements VoxelConstructor and QuadConstructor to build an example terrain.
 */

class PerlinConstructor: public VoxelConstructor {
 private:
//	noise::module::Perlin mPerlin;
 public:
	PerlinConstructor();
	virtual ~PerlinConstructor();
	GLboolean calculateActiveVoxel(GLfloat x, GLfloat z, GLfloat y);
	GLfloat calculateHeight(GLfloat x, GLfloat z);
};

} /* framework */
} /* fillwave */
