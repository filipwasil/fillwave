/*
 * Conversion.h
 *
 *  Created on: Mar 28, 2014
 *      Author: Filip Wasil
 */

#ifndef CONVERSION_H_
#define CONVERSION_H_

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
