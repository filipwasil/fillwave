/*
 * Programmable.h
 *
 *  Created on: May 15, 2015
 *      Author: filip
 */

#ifndef SRC_MODELS_PROGRAMMABLE_H_
#define SRC_MODELS_PROGRAMMABLE_H_

#include <fillwave/models/Entity.h>
#include <fillwave/models/effects/Effect.h>

namespace fillwave {
namespace framework {

/*! \class Programmable
 * \brief Entity for which is it possible to add/remove Effect objects.
 */

class Programmable: public Entity {
public:
	Programmable(pProgram program);

	virtual ~Programmable() = default;

	/* Effects */
	void addEffect(pEffect effect);
	void removeEffect(pEffect effect);
	void drawWithEffects(Camera& camera);
	void drawWithEffectsDR(Camera& camera);

protected:
	pProgram mProgram;

	std::vector<pEffect> mEffects;
};

} /* framework */
} /* fillwave */

#endif /* SRC_MODELS_PROGRAMMABLE_H_ */
