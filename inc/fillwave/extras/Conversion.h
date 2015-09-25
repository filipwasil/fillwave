/*
 * Conversion.h
 *
 *  Created on: Mar 28, 2014
 *      Author: Filip Wasil
 */

#ifndef CONVERSION_H_
#define CONVERSION_H_

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

#include <fillwave/Math.h>
#include <fillwave/Assets.h>

namespace fillwave {

#ifdef FILLWAVE_COMPILATION_TINY_ASSET_LOADER

#else

glm::mat4 assimpToGlmMat4(aiMatrix4x4 matrix);
glm::vec3 assimpToGlmVec3(aiVector3D vector);
glm::quat assimpToGlmQuat(aiQuaternion quaternion);
glm::vec4 assimpToGlmVec4(aiColor4D vector);

#endif

} /* fillwave */

#endif /* CONVERSION_H_ */
