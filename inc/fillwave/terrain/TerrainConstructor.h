/*
 * TerrainConstructor.h
 *
 *  Created on: Apr 20, 2015
 *      Author: Filip Wasil
 */

#ifndef SRC_TERRAIN_TERRAINCONSTRUCTOR_H_
#define SRC_TERRAIN_TERRAINCONSTRUCTOR_H_

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

/*! \class TerrainConstructor
 * \brief Implements height map calculation function.
 */

class TerrainConstructor {
public:
	TerrainConstructor();
	virtual ~TerrainConstructor();
	virtual GLfloat calculateHeight(GLfloat x, GLfloat z) = 0;
};

} /* models */
} /* fillwave */

#endif /* SRC_TERRAIN_TERRAINCONSTRUCTOR_H_ */
