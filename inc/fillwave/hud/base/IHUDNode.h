/*
 * IHUDNode.h
 *
 *  Created on: Jan 10, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_HUD_IHUD_NODE_H_
#define INC_FILLWAVE_HUD_IHUD_NODE_H_

#include <fillwave/core/texturing/TextureRegion.h>

namespace fillwave {
namespace framework {

class IHUDNode {
public:
	IHUDNode(pTextureRegion texture)
			: mTexture(texture) {

	}

	IHUDNode(pTexture2D texture)
			: mTexture(std::make_shared<core::TextureRegion>(texture)) {

	}

	virtual ~IHUDNode() = default;

	virtual void draw() = 0;

protected:
	pTextureRegion mTexture;
};

} /* namespace framework */
typedef std::shared_ptr<framework::IHUDNode> pIHUDNode;
} /* namespace fillwave */

#endif /* INC_FILLWAVE_HUD_IHUD_NODE_H_ */
