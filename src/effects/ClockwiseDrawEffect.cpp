/*
 * ClockwiseDrawEffect.cpp
 *
 *  Created on: 24 Jul 2014
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

#include <fillwave/effects/ClockwiseDrawEffect.h>

namespace fillwave {
namespace effects {

ClockwiseDrawEffect::ClockwiseDrawEffect() {

}

ClockwiseDrawEffect::~ClockwiseDrawEffect() {

}

void ClockwiseDrawEffect::preDrawAction(core::Program* program) {
	glFrontFace(GL_CW);
}

void ClockwiseDrawEffect::postDrawAction(core::Program* program) {
	glFrontFace(GL_CCW);
}

void ClockwiseDrawEffect::stopAction(core::Program* program) {

}

void ClockwiseDrawEffect::startAction(core::Program* program) {

}

} /* effects */
} /* fillwave */
