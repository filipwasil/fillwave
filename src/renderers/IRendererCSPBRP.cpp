/*
 * IRendererCSPBRP.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: filip
 */

#include <fillwave/renderers/IRendererCSPBRP.h>
#include <fillwave/models/Entity.h>
#include <fillwave/models/Skybox.h>
#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/Log.h>

FLOGINIT_DEFAULT()

namespace fillwave {
namespace framework {

void IRendererCSPBRP::update(Entity* entity) {
	GLuint programId = entity->getRenderData().mHandles[RenderData::eRenderHandleProgram];
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
//			mLightManager->pushLightUniforms(mProgram.get()); todo
//			mLightManager->bindShadowmaps(); todo
			// Evaluate animations
				// other stuff
			for (auto& drawData : container) {
//				uniform update todo

				drawData.mStatus.bVAO
					? core::bindVAO(drawData.mHandles[eRenderHandleVAO]) : (void)0;

				drawData.mStatus.bDiffuse
					? core::bindTexture(GL_TEXTURE_2D, FILLWAVE_TEXTURE_TYPE_DIFFUSE, drawData.mHandles[eRenderHandleDiffuse]) : (void)0;

				drawData.mStatus.bNormal
					? core::bindTexture(GL_TEXTURE_2D, FILLWAVE_TEXTURE_TYPE_NORMALS, drawData.mHandles[eRenderHandleNormal]) : (void)0;

				drawData.mStatus.bSpecular
					? core::bindTexture(GL_TEXTURE_2D, FILLWAVE_TEXTURE_TYPE_SPECULAR, drawData.mHandles[eRenderHandleSpecular]) : (void)0;

				drawData.mStatus.bIndexDraw
					? glDrawElements(drawData.mMode, drawData.mCount, drawData.mDataType, drawData.mIndicesPointer)
							: glDrawArrays(drawData.mMode, drawData.mFirst, drawData.mCount);

				FLOG_CHECK("Draw failed");

				drawData.mStatus.bVAO ? core::VertexArray::unbindVAO() : (void)0;

				core::Texture2D::unbind2DTextures();
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
