/*
 * EmiterPointStep.cpp
 *
 *  Created on: Sep 10, 2014
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * filip.wasil@gmail.com
 *
 */

#include <fillwave/particles/EmiterPointStep.h>

#include <fillwave/Fillwave.h>

namespace fillwave {
namespace particles {

EmiterPointStep::EmiterPointStep(Engine* engine,
      GLint howMany,
      GLenum blendingSource,
      GLenum blendingDestination,
      pTexture texture)
:EmiterPoint(engine,
 howMany,
 100, //size
 1, //lifetime
 texture,
 glm::vec4(1.0,1.0,1.0,0.0), // color
 blendingSource,
 blendingDestination,
 GL_FALSE,
 1.0) {

}

EmiterPointStep::~EmiterPointStep() {

}

} /* particles */
} /* fillwave */
