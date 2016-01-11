/*
 * Indicator.h
 *
 *  Created on: Jan 11, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_HUD_INDICATOR_H_
#define INC_FILLWAVE_HUD_INDICATOR_H_

#include <fillwave/hud/base/IHUDNode.h>
#include <fillwave/core/rendering/Texture2DRenderable.h>

namespace fillwave {
namespace framework {

class Indicator: public IHUDNode {
public:
	Indicator(pTexture2D texture);
	virtual ~Indicator();

	void draw() override;
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_HUD_INDICATOR_H_ */
