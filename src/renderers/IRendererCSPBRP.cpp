/*
 * IRendererCSPBRP.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: filip
 */

#include <fillwave/renderers/IRendererCSPBRP.h>
#include <fillwave/models/Entity.h>
#include <fillwave/models/Skybox.h>

#include <fillwave/Log.h>

FLOGINIT_DEFAULT()

namespace fillwave {
namespace framework {

void IRendererCSPBRP::update(GLuint* programId, Entity* entity) {
	std::vector<RenderData> item (1, entity->getRenderData());
	if (mRenderPasses.find(*programId) != mRenderPasses.end()) {
		mRenderPasses[*programId].push_back(item);
	} else {
		std::vector<std::vector<RenderData>> container;
		container.push_back(item);
		mRenderPasses[*programId] = container;
	}
}

void IRendererCSPBRP::draw(ICamera& camera) {
	if (mSkybox) {
		mSkybox->draw(camera);
	}
	glClear(GL_DEPTH_BUFFER_BIT);
	for (auto& program : mRenderPasses) {
		core::Program::useProgram(program.first);
		for (auto& container : program.second) {
//			mLightManager->pushLightUniforms(mProgram.get());
//			mLightManager->bindShadowmaps();
			// other stuff
			for (auto& drawData : container) {
//				uniform update
//				RenderData
				drawData.mStatus.bVAO ? core::VertexArray::bindVAO(drawData.mHandles[eRenderHandleVAO]) : (void)0;
//
//				bindTextures();
				/* Perform index drawing */
//				glDrawElements(mRenderMode, mIBO->getElements(),
//				GL_UNSIGNED_INT, (GLvoid*) 0);
//				FLOG_CHECK("glDrawElements failed");
//			} else {
//				/* Perform array drawing */
//				glDrawArrays(mRenderMode, 0, mVBO->getElements());
//				FLOG_CHECK("glDrawArrays failed");
//				mVAO->unbind();
//
//				core::Texture2D::unbind2DTextures();
			}
		}
	}
}

void IRendererCSPBRP::reset(GLuint /*width*/, GLuint /*height*/) {
	mFlagReload = true;
}

void IRendererCSPBRP::clear() {
	mFlagReload= true;

	size_t predictedSize = mRenderPasses.size() + 1;
	mRenderPasses.clear();
	mRenderPasses.reserve(predictedSize);
}


} /* namespace framework */
} /* namespace fillwave */
