/*
 * TextureOnly.h
 *
 *  Created on: Dec 5, 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTUREONLY_H_
#define TEXTUREONLY_H_

#include <fillwave/effects/Effect.h>

namespace fillwave {
namespace effects {

/*! \class TextureOnly
 * \brief Effect to color the model with texture only (exclude light effects and shadows).
 */

class TextureOnly: public Effect {
public:
	TextureOnly() = default;
	virtual ~TextureOnly() = default;
	void preDrawAction(core::Program* program);
	void postDrawAction(core::Program* program);
	void stopAction(core::Program* program);
	void startAction(core::Program* program);
};

} /* effects*/
} /* fillwave */

#endif /* TEXTUREONLY_H_ */
