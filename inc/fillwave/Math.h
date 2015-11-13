/*
 * Math.h
 *
 *  Created on: Dec 5, 2014
 *      Author: Filip Wasil
 */

#ifndef MATH_H_
#define MATH_H_

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2         3.14159265358979323846 * 0.5
#endif

namespace fillwave {
static const float F_PI = static_cast<float>(M_PI);
static const float F_PI_2 = static_cast<float>(M_PI_2);
} /* fillwave */

#endif /* MATH_H_ */
