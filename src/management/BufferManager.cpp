/*
 * BufferManager.cpp
 *
 *  Created on: 15 Apr 2014
 *      Author: Filip Wasil
 */

#include <fillwave/management/BufferManager.h>
#include <algorithm>

FLOGINIT("BufferManager", FERROR | FFATAL)

namespace fillwave {
namespace manager {

pVertexArray BufferManager::getVAO(models::Reloadable* user) {
	VAOObject* mVAOObject = new VAOObject();
	mVAOObject->mVAOUser = user;
	pVertexArray shared(new core::VertexArray());
	mVAOObject->mVAO = shared;
	mVAOObjects.push_back(puVAOObject(mVAOObject));
	return shared;
}

void BufferManager::reload() {
	collectGarbage();
	for (auto& it : mVAOObjects) {
		it->mVAO.lock()->reload();
		it->mVAOUser->reload();
	}
}

void BufferManager::collectGarbage() {
	auto _find_useless_VAOObjects =
			[](puVAOObject arrayObject) -> bool {bool result = true; if(arrayObject->mVAO.lock()) {result = false;}return result;};
	auto _begin = mVAOObjects.begin();
	auto _end = mVAOObjects.end();
	auto it = std::remove_if(_begin, _end, _find_useless_VAOObjects);
	mVAOObjects.erase(it, _end);
}

} /* manager */
} /* fillwave */
