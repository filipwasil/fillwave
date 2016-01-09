/*
 * RendererPBRP.cpp
 *
 *  Created on: Dec 31, 2015
 *      Author: filip
 */

#include <fillwave/renderers/RendererPBRP.h>
#include <fillwave/core/pipeline/Program.h>
#include <fillwave/models/Entity.h>
#include <fillwave/models/Skybox.h>

#include <fillwave/Log.h>

FLOGINIT_DEFAULT()

namespace fillwave {
namespace framework {

void RendererPBRP::onScreenResize(GLuint /*width*/, GLuint /*height*/) {

}

void RendererPBRP::update(GLuint* programId, Entity* entity) {
	static int d =0;
	if (mRenderPasses.find(*programId) != mRenderPasses.end()) {
		FLOG_DEBUG("UPDATE PROGRAM VECTOR: %d", d++);
		mRenderPasses[*programId].push_back(entity);
	} else {
		FLOG_DEBUG("UPDATE PROGRAM NEW VECTOR: %d", d++);
		std::vector<Entity*> vector;
		vector.push_back(entity);
		mRenderPasses[*programId] = vector;
	}
}

void RendererPBRP::draw(ICamera& camera) {
	if (mSkybox) {
		mSkybox->draw(camera);
	}
	glClear(GL_DEPTH_BUFFER_BIT);
	for (auto& program : mRenderPasses) {
		core::Program::useProgram(program.first);
		for (auto& node : program.second) {
			if (node->mFlagAttachedDetached) {
				mFlagReload = true;
				node->mFlagAttachedDetached = false;
			}
			node->drawPBRP(camera);
		}
	}
}

void RendererPBRP::reset() {
	size_t predictedSize = mRenderPasses.size() + 1;
	mRenderPasses.clear();
	mRenderPasses.reserve(predictedSize);
}

} /* namespace framework */
} /* namespace fillwave */
