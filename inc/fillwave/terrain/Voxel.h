/*
 * Voxel.h
 *
 *  Created on: Dec 1, 2014
 *      Author: Filip Wasil
 */

#ifndef VOXEL_H_
#define VOXEL_H_

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

namespace fillwave {
namespace terrain {

/*! \class Voxel
 * \brief Single terrain element.
 */

class Voxel {
public:
	Voxel();
	~Voxel();
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
