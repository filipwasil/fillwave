/*
 * Voxel.h
 *
 *  Created on: Dec 1, 2014
 *      Author: Filip Wasil
 */

#ifndef VOXEL_H_
#define VOXEL_H_

#include <fillwave/OpenGL.h>

namespace fillwave {
namespace terrain {

/*! \class Voxel
 * \brief Single terrain element.
 */

class Voxel {
public:
	Voxel();
	~Voxel() = default;
	GLboolean isActive();
	void setActive(GLboolean active);
	void setType(GLint type);

private:
	GLboolean mActive;
	GLint mType;
};

} /* models */
} /* fillwave*/

#endif /* VOXEL_H_ */
