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

/**
 * Data structure containing each Sampler instance info.
 */
typedef Composition<pSampler, TPolicyShared<core::Sampler>, GLint>
SamplerObject;

/**
 * Sampler manager
 */
typedef ManagerComposite<std::unique_ptr<SamplerObject>, pSampler, GLint,
        UINT_MAX, TPolicyUnique<SamplerObject>, GLint> ManagerSamplers;

} /* framework */
} /* fillwave */

#endif /* SAMPLERMANAGER_H_ */
