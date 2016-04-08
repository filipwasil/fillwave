/*
 * Voxel.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: filip
 *
 */

#include <fillwave/models/terrain/Voxel.h>

namespace fillwave {
namespace framework {

Voxel::Voxel() :
	mType(0), mActive(GL_TRUE) {
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

} /* framework */
} /* fillwave */
