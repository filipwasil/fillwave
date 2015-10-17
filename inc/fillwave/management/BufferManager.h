/*
 * BufferManager.h
 *
 *  Created on: 15 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef BUFFERMANAGER_H_
#define BUFFERMANAGER_H_

#include <fillwave/core/buffers/Buffer.h>
#include <fillwave/models/Reloadable.h>

namespace fillwave {
namespace manager {

struct VAOObject {
	models::Reloadable* mVAOUser;
	pwVertexArray mVAO;
};

typedef std::shared_ptr<VAOObject> puVAOObject;

/*! \class BufferManager
 * \brief Not used.
 */

class BufferManager {
public:
	BufferManager() = default;

	virtual ~BufferManager() = default;

	void collectGarbage();

	void reload();

	pVertexArray getVAO(models::Reloadable* renderable);

private:
	std::vector<puVAOObject> mVAOObjects;
};

} /* manager */
typedef std::unique_ptr<manager::BufferManager> puBufferManager;
} /* fillwave */

#endif /* BUFFERMANAGER_H_ */
