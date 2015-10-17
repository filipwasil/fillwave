/*
 * SamplerManager.cpp
 *
 *  Created on: Apr 18, 2014
 *      Author: filip
 */

#include <fillwave/management/SamplerManager.h>

#include <fillwave/extras/Log.h>

FLOGINIT("SamplerManager", FERROR | FFATAL)

namespace fillwave {
namespace manager {

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
