/*
 * Parameter.h
 *
 *  Created on: Jul 25, 2014
 *      Author: Filip Wasil
 */

#ifndef PARAMETER_H_
#define PARAMETER_H_

#include <fillwave/OpenGL.h>
#include <vector>

namespace fillwave {
namespace core {

/*! Parameter
 * \brief Texture and Sampler parameter class.
 */

typedef std::pair<GLenum, GLenum> Parameter;

/*! ParameterList
 * \brief List of Parameter class.
 */

typedef std::vector<Parameter> ParameterList;

} /* core */
} /* fillwave */

#endif /* PARAMETER_H_ */
