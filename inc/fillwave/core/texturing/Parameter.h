/*
 * Parameter.h
 *
 *  Created on: Jul 25, 2014
 *      Author: Filip Wasil
 */

#ifndef PARAMETER_H_
#define PARAMETER_H_

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
