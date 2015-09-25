/*
 * Fence.h
 *
 *  Created on: Jun 4, 2014
 *      Author: Filip Wasil
 */

#ifndef FENCE_H_
#define FENCE_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/OpenGL.h>

#include <memory>

namespace fillwave {
namespace core {

/*! \class Fence
 * \brief Sets a fence for a gpu to wait.
 *
 */

class Fence {
public:
	Fence(GLenum target = GL_SYNC_GPU_COMMANDS_COMPLETE);

	virtual ~Fence();

	void wait(unsigned long long timeoutSpecifier = GL_TIMEOUT_IGNORED);

private:
	GLsync mHandle;
};

} /* core */
typedef std::unique_ptr<core::Fence> puFence;
} /* fillwave */

#endif /* FENCE_H_ */
