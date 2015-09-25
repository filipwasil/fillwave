/*
 * BoostColor.cpp
 *
 *  Created on: Dec 5, 2014
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

#include <fillwave/effects/BoostColor.h>

namespace fillwave {
namespace effects {

BoostColor::BoostColor(GLfloat boost)
		: mBoost(boost) {

}

BoostColor::~BoostColor() {

}

void BoostColor::preDrawAction(core::Program* program) {
	program->uniformPush("uBoostColorEffect", true);
	program->uniformPush("uBoostColorFactor", mBoost);
}

void BoostColor::postDrawAction(core::Program* program) {
	program->uniformPush("uBoostColorEffect", false);
}

void BoostColor::stopAction(core::Program* program) {
	program->uniformPush("uBoostColorEffect", false);
}

void BoostColor::startAction(core::Program* program) {
	program->uniformPush("uBoostColorEffect", true);
}

} /* effects*/
} /* fillwave */
