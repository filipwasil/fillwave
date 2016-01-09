/*
 * ConditionalRender.cpp
 *
 *  Created on: May 17, 2015
 *      Author: filip
 */

#include <fillwave/core/operations/ConditionalRender.h>
#include <fillwave/Log.h>
#include <memory>

#ifdef FILLWAVE_GLES_3_0
#else

FLOGINIT("ConditionalRender", FERROR | FFATAL)

namespace fillwave {
namespace core {

ConditionalRender::ConditionalRender(GLenum mode)
		: mMode(mode) {

}

void ConditionalRender::begin(GLuint querryID) const {
	glBeginConditionalRender(querryID, mMode);
}

void ConditionalRender::end() const {
	glEndConditionalRender();
}

} /* core */
} /* fillwave */

#endif
