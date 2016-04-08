/*
 * Fence.h
 *
 *  Created on: Jun 4, 2014
 *      Author: Filip Wasil
 */

#ifndef FENCE_H_
#define FENCE_H_

#include <fillwave/OpenGL.h>

#include <memory>

namespace fillwave {
namespace core {

/*! \class Fence
 * \brief Sets a fence for a gpu to wait.
 */

class Fence {
  public:
	Fence(GLenum target = GL_SYNC_GPU_COMMANDS_COMPLETE);

	virtual ~Fence();

	void wait(unsigned long long timeoutSpecifier = GL_TIMEOUT_IGNORED) const;

  private:
	GLsync mHandle;
};

} /* core */
typedef std::unique_ptr<core::Fence> puFence;
} /* fillwave */

#endif /* FENCE_H_ */
