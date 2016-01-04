/*
 * RendererPBRP.cpp
 *
 *  Created on: Dec 31, 2015
 *      Author: filip
 */

#include <fillwave/renderers/RendererPBRP.h>
#include <fillwave/core/pipeline/Program.h>
#include <fillwave/models/Entity.h>
#include <fillwave/Log.h>

FLOGINIT_DEFAULT()

namespace fillwave {
namespace framework {

void RendererPBRP::update(GLuint programId, Entity* entity) {
	if (entity->getTreeRefresh()) {
		setRefresh();
		entity->setTreeRefresh(false);
	}
	if (mRenderPasses.find(programId) != mRenderPasses.end()) {
		mRenderPasses[programId].push_back(entity);
	} else {
		std::vector<Entity*> vector;
		vector.push_back(entity);
		mRenderPasses[programId] = vector;
	}
}

void RendererPBRP::draw(ICamera& camera) {
	for (auto& program : mRenderPasses) {
		core::Program::useProgram(program.first);
		for (auto& node : program.second) {
			FLOG_ERROR("DEBUG %u", program.first);
			node->drawPBRP(camera);
		}
	}
}

void RendererPBRP::reset() {
	size_t predictedSize = mRenderPasses.size() + 1;
	mRenderPasses.clear();
	mRenderPasses.reserve(predictedSize);
	setRefresh();
}

} /* namespace framework */
} /* namespace fillwave */
