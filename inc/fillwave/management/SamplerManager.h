/*
 * SamplerManager.h
 *
 *  Created on: Apr 18, 2014
 *      Author: filip
 */

#ifndef SAMPLERMANAGER_H_
#define SAMPLERMANAGER_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/core/texturing/Sampler.h>

namespace fillwave {
namespace manager {

/*! \class SamplerManager
 *
 * \brief Not used.
 *
 */

class SamplerManager {
public:
	SamplerManager();
	virtual ~SamplerManager();

	pSampler get(GLint textureUnit);

	void reload();
private:
	std::vector<pSampler> mSamplers;
};

} /* manager */
typedef std::unique_ptr<manager::SamplerManager> puSamplerManager;
} /* fillwave */

#endif /* SAMPLERMANAGER_H_ */
