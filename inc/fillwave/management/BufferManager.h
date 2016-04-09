/*
 * BufferManager.h
 *
 *  Created on: 15 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef BUFFERMANAGER_H_
#define BUFFERMANAGER_H_

#include <fillwave/core/buffers/Buffer.h>
#include <fillwave/models/base/IReloadable.h>

namespace fillwave {
namespace framework {

/*! \class ManagerBuffers
 * \brief Connects VAO pointer and VAO's user pointer in single class.
 */
typedef TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::VertexArray,
		IReloadable*> ManagerBuffers;

} /* framework */
} /* fillwave */

#endif /* BUFFERMANAGER_H_ */
