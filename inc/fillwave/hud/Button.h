/*
 * Button.h
 *
 *  Created on: Jan 11, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_HUD_BUTTON_H_
#define INC_FILLWAVE_HUD_BUTTON_H_

#include <fillwave/hud/base/IHUDNode.h>
#include <fillwave/common/IPickable.h>

namespace fillwave {
namespace framework {

class Button: public IHUDNode, public IPickable {
public:
	Button(pTexture2D texture, GLfloat xPosition, GLfloat yPosition);
	virtual ~Button();

	void draw() override;

	virtual void onPicked() override;
	virtual void onUnpicked() override;
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_HUD_BUTTON_H_ */
