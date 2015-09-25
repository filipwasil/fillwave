/*
 * SamplerManager.cpp
 *
 *  Created on: Apr 18, 2014
 *      Author: filip
 */

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


#include <fillwave/management/SamplerManager.h>

#include <fillwave/extras/Log.h>

FLOGINIT("SamplerManager", FERROR | FFATAL)

namespace fillwave {
namespace manager {

SamplerManager::SamplerManager() {

}

SamplerManager::~SamplerManager() {

}

pSampler SamplerManager::get(GLint textureUnit) {
   for (auto& it : mSamplers) {
      return it;
   }
   core::Sampler* so = new core::Sampler(textureUnit);
   mSamplers.push_back(pSampler(so));
   return mSamplers.back();
}

void SamplerManager::reload() {
   for (auto& it : mSamplers) {
      it->reload();
   }
}

} /* manager */
} /* fillwave */
