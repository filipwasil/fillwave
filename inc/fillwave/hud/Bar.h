/*
 * Bar.h
 *
 *  Created on: Jan 11, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_HUD_BAR_H_
#define INC_FILLWAVE_HUD_BAR_H_

#include <fillwave/hud/Indicator.h>

namespace fillwave {
namespace framework {

class Bar: public Indicator {
public:
	Bar(pTexture2DRenderable texture);
	virtual ~Bar();
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_HUD_BAR_H_ */
