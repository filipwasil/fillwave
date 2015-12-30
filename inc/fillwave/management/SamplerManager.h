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
namespace framework {

/*! \class SamplerManager
 * \brief returns sampler
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

} /* framework */
typedef std::unique_ptr<framework::SamplerManager> puSamplerManager;
} /* fillwave */

#endif /* SAMPLERMANAGER_H_ */
