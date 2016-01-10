/*
 * IHUD.h
 *
 *  Created on: Jan 10, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_HUD_IHUD_H_
#define INC_FILLWAVE_HUD_IHUD_H_

#include <fillwave/core/texturing/TextureRegion.h>

namespace fillwave {
namespace framework {

class IHUD {
public:
	IHUD(pTextureRegion texture)
			: mTexture(texture) {

	}

	IHUD(pTexture2D texture)
			: mTexture(std::make_shared<core::TextureRegion>(texture)) {

	}

	virtual ~IHUD() = default;

	virtual void draw() = 0;

protected:
	pTextureRegion mTexture;
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_HUD_IHUD_H_ */
