/*
 * SamplerManager.h
 *
 *  Created on: Apr 18, 2014
 *      Author: filip
 */

#ifndef SAMPLERMANAGER_H_
#define SAMPLERMANAGER_H_

#include <fillwave/core/texturing/Sampler.h>

namespace fillwave {
namespace manager {

/*! \class SamplerManager
 * \brief Not used.
 */

class SamplerManager {
public:
	SamplerManager() = default;
	virtual ~SamplerManager() = default;

	pSampler get(GLint textureUnit);

	void reload();
private:
	std::vector<pSampler> mSamplers;
};

} /* manager */
typedef std::unique_ptr<manager::SamplerManager> puSamplerManager;
} /* fillwave */

#endif /* SAMPLERMANAGER_H_ */
