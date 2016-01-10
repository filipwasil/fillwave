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

typedef framework::TreePtr<pIHUDNode> HUD;
typedef std::shared_ptr<HUD> pHUD;
typedef std::unique_ptr<HUD> puHUD;

} /* namespace fillwave */

#endif /* INC_FILLWAVE_HUD_BASE_HUD_H_ */
