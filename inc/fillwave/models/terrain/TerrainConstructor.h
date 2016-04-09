/*
 * TerrainConstructor.h
 *
 *  Created on: Apr 20, 2015
 *      Author: Filip Wasil
 */

#ifndef SRC_TERRAIN_TERRAINCONSTRUCTOR_H_
#define SRC_TERRAIN_TERRAINCONSTRUCTOR_H_

#include <fillwave/OpenGL.h>

namespace fillwave {
namespace framework {

/*! \class TerrainConstructor
 * \brief Implements height map calculation function.
 */

class TerrainConstructor {
 public:
	TerrainConstructor() = default;
	virtual ~TerrainConstructor() = default;
	virtual GLfloat calculateHeight(GLfloat x, GLfloat z) = 0;
};

} /* framework */
} /* fillwave */

#endif /* SRC_TERRAIN_TERRAINCONSTRUCTOR_H_ */
