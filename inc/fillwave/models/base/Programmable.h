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
	Programmable(core::Program* program);

	virtual ~Programmable() = default;

	void addEffect(pIEffect effect);
	void removeEffect(pIEffect effect);
	void drawWithEffects(ICamera& camera);
	void drawWithEffectsDR(ICamera& camera);
	void drawWithEffectsPBRP(ICamera& camera);

 protected:
	core::Program* mProgram;

	std::vector<pIEffect> mEffects;
};

} /* framework */
} /* fillwave */

#endif /* SRC_MODELS_PROGRAMMABLE_H_ */
