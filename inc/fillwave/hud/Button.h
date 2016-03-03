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
class Engine;
namespace framework {

/*! \class Button
 * \brief Pickable hud node.
 */

class Button: public IHUDNode, public IPickable {
public:
	Button(
			Engine* engine,
			const pTexture2D& texture,
			glm::vec2 position,
			glm::vec2 scale);
	virtual ~Button() = default;

	/* IPickable */
	virtual void pick(glm::vec3 color) override;
	virtual void unpick() override;
	virtual void onPicked() override;
	virtual void onUnpicked() override;
};

} /* namespace framework */
typedef std::shared_ptr<framework::Button> pButton;
} /* namespace fillwave */

#endif /* INC_FILLWAVE_HUD_BUTTON_H_ */
