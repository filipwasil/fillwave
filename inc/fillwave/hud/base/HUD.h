/*
 * HUD.h
 *
 *  Created on: Jan 10, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_HUD_BASE_HUD_H_
#define INC_FILLWAVE_HUD_BASE_HUD_H_

#include <fillwave/hud/base/IHUDNode.h>
#include <fillwave/models/base/TreePtr.h>

namespace fillwave {
class Engine;
namespace framework {

class HUD: public TreePtr<pIHUDNode> {
public:
	HUD() = default;
	virtual ~HUD() = default;

	virtual void draw();
};

} /* namespace framework */
typedef std::shared_ptr<framework::HUD> pHUD;
typedef std::unique_ptr<framework::HUD> puHUD;
} /* namespace fillwave */

#endif /* INC_FILLWAVE_HUD_BASE_HUD_H_ */
