/*
 * RendererFR.cpp
 *
 *  Created on: Jan 4, 2016
 *      Author: filip
 */

#include <fillwave/renderers/RendererFR.h>
#include <fillwave/models/Entity.h>

namespace fillwave {
namespace framework {

void RendererFR::update(GLuint* /*programId*/, Entity* entity) {
	mRenderPasses.push_back(entity);
}

void RendererFR::draw(ICamera& camera) {
	for (auto& node : mRenderPasses) {
		if (node->mFlagAttachedDetached) {
			mFlagReload = true;
			node->mFlagAttachedDetached = false;
		}
		node->draw(camera);
	}
}

void RendererFR::reset() {
	size_t predictedSize = mRenderPasses.size() + 1;
	mRenderPasses.clear();
	mRenderPasses.reserve(predictedSize);
}

} /* namespace framework */
} /* namespace fillwave */
