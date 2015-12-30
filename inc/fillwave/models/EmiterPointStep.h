/*
 * EmiterPointStep.h
 *
 *  Created on: Sep 10, 2014
 *      Author: Filip Wasil
 */

#ifndef EmiterPointStep_H_
#define EmiterPointStep_H_

#include <fillwave/models/base/EmiterPoint.h>
#include <fillwave/models/animations/Key.h>

namespace fillwave {
class Engine;
namespace framework {

/*! \class EmiterPointStep
 * \brief Not used.
 */

class EmiterPointStep: public EmiterPoint {
public:
	EmiterPointStep(
			Engine* engine,
			GLint howMany,
			GLenum blendingSource,
			GLenum blendingDestination,
			pTexture texture);

	virtual ~EmiterPointStep() = default;
};

} /* framework */
} /* fillwave */

#endif /* EmiterPointStep_H_ */
