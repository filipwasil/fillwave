/*
 * Reloadable.cpp
 *
 *  Created on: May 24, 2015
 *      Author: Filip Wasil
 */

#include <fillwave/models/base/Reloadable.h>
#include <fillwave/Fillwave.h>

FLOGINIT("Reloadable", FERROR | FFATAL)

namespace fillwave {
namespace framework {

Reloadable::Reloadable(Engine* engine)
		:
				mVAO(engine->storeVAO(this)),
				mSampler(engine->storeSO(FILLWAVE_DIFFUSE_UNIT)) {
	mSampler->bind();
	mSampler->setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	mSampler->setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	mSampler->setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
}

void Reloadable::reload() {
	initBuffers();
	initPipeline();
	initVBO();
	initVAO();
	initUniformsCache();
}

} /* framework */
} /* fillwave */
