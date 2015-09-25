/*
 * BufferManager.cpp
 *
 *  Created on: 15 Apr 2014
 *      Author: Filip Wasil
 */

#include <fillwave/management/BufferManager.h>
#include <algorithm>

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * filip.wasil@gmail.com
 *
 */

FLOGINIT("BufferManager", FERROR | FFATAL)

namespace fillwave {
namespace manager {

BufferManager::BufferManager() {

}

BufferManager::~BufferManager() {

}

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
   auto _find_useless_VAOObjects = [](puVAOObject arrayObject) -> bool { bool result = true; if(arrayObject->mVAO.lock()) { result = false; } return result; };
   auto _begin = mVAOObjects.begin();
   auto _end = mVAOObjects.end();
   auto it = std::remove_if(_begin, _end, _find_useless_VAOObjects);
   mVAOObjects.erase(it, _end);
}

} /* manager */
} /* fillwave */
