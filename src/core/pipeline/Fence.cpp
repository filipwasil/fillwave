/*
 * Fence.cpp
 *
 *  Created on: Jun 4, 2014
 *      Author: filip
 */

#include <fillwave/core/pipeline/Fence.h>

namespace fillwave {
namespace core {

Fence::Fence(GLenum target) :
	mHandle(glFenceSync(target, 0)) {

}

Fence::~Fence() {
	glDeleteSync(mHandle);
}

void Fence::wait(unsigned long long timeoutSpecifier) const {
	glWaitSync(mHandle, 0, timeoutSpecifier);
}

} /* core */
} /* fillwave */
