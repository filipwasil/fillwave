/*
 * BufferManager.h
 *
 *  Created on: 15 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef BUFFERMANAGER_H_
#define BUFFERMANAGER_H_

#include <fillwave/core/buffers/Buffer.h>
#include <fillwave/models/base/Reloadable.h>

namespace fillwave {
namespace framework {

/*! \class VAOObject
 * \brief Connects VAO pointer and VAO's user pointer in single class.
 */

struct VAOObject {
	Reloadable* mVAOUser;
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

	pVertexArray getVAO(Reloadable* renderable);

private:
	std::vector<puVAOObject> mVAOObjects;
};

} /* framework */
typedef std::unique_ptr<framework::BufferManager> puBufferManager;
} /* fillwave */

#endif /* BUFFERMANAGER_H_ */
