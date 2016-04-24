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

typedef TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::Sampler,
        GLint, GLint> ManagerSamplers;

} /* framework */
} /* fillwave */

#endif /* SAMPLERMANAGER_H_ */