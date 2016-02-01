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
struct SamplerObject {
	SamplerObject(GLint unit)
			: mTextureUnit(unit),
			  mContent(std::make_shared<core::Sampler>(unit)) {

	}

	~SamplerObject() = default;

	GLint mTextureUnit;
	pSampler mContent;
};

/**
 * Sampler manager
 */
typedef ManagerNested<std::unique_ptr<SamplerObject>, pSampler, GLint, UINT_MAX, PolicyUnique<SamplerObject>,
		GLint> ManagerSamplers;

} /* framework */
} /* fillwave */

#endif /* SAMPLERMANAGER_H_ */
