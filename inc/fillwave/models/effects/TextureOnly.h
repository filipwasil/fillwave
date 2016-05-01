/*
 * TextureOnly.h
 *
 *  Created on: Dec 5, 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTUREONLY_H_
#define TEXTUREONLY_H_

#include <fillwave/models/effects/Effect.h>

namespace fillwave {
namespace framework {

/*! \class TextureOnly
 * \brief Effect to color the model with texture only (exclude light effects and shadows).
 */

class TextureOnly: public IEffect {
 public:
	TextureOnly() = default;
	virtual ~TextureOnly() = default;
	void preDrawAction(core::Program* program) override;
	void postDrawAction(core::Program* program) override;
	void stopAction(core::Program* program) override;
	void startAction(core::Program* program) override;
};

} /* framework*/
} /* fillwave */

#endif /* TEXTUREONLY_H_ */
