/*
 * HUD.cpp
 *
 *  Created on: Jan 11, 2016
 *      Author: filip
 */

#include <fillwave/hud/Button.h>
#include <fillwave/Fillwave.h>

namespace fillwave {
namespace framework {

void HUD::draw() {
	for (auto& it : mChildren) {
		it->draw();
	}
}

} /* namespace framework */
} /* namespace fillwave */
