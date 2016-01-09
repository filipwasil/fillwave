/*
 * RendererFR.cpp
 *
 *  Created on: Jan 4, 2016
 *      Author: filip
 */

#include <fillwave/renderers/RendererFR.h>
#include <fillwave/models/Entity.h>
#include <fillwave/models/Skybox.h>

namespace fillwave {
namespace framework {

void RendererFR::onScreenResize(GLuint /*width*/, GLuint /*height*/) {

}

void RendererFR::update(GLuint* /*programId*/, Entity* entity) {
	mRenderPasses.push_back(entity);
}

void RendererFR::draw(ICamera& camera) {
	if (mSkybox) {
		mSkybox->draw(camera);
	}
	glClear(GL_DEPTH_BUFFER_BIT);
	for (auto& node : mRenderPasses) {
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
