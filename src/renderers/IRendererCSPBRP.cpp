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
#include <fillwave/management/LightSystem.h>

FLOGINIT_DEFAULT()

namespace fillwave {
namespace framework {

IRendererCSPBRP::IRendererCSPBRP(LightManager* lightManager) : mLightManager(
	   lightManager) {

}

void IRendererCSPBRP::update(IRenderable* renderable) {
	RenderItem item;
	renderable->getRenderItem(item);
	GLuint programId = item.mHandles[RenderItem::eRenderHandleProgram];
	std::vector<RenderItem> items (1, item);
	if (mRenderPasses.find(programId) != mRenderPasses.end()) {
		mRenderPasses[programId].push_back(items);
	} else {
		std::vector<std::vector<RenderItem>> container;
		container.push_back(items);
		mRenderPasses[programId] = container;
	}
}

void IRendererCSPBRP::draw(ICamera& camera) {
	if (mSkybox) {
		mSkybox->draw(camera);
	}
	glClear(GL_DEPTH_BUFFER_BIT);
	for (auto& program : mRenderPasses) {
		core::Program::useProgram(program.first);
// 	Light manager supports only Fillwave programs
//		mLightManager->pushLightUniforms(mProgram.get());
//		mLightManager->bindShadowmaps();
		for (auto& container : program.second) {
			// Evaluate animations
			// other stuff
			// xxx todo Is Lambda fast enough ?
			for (auto& renderItem : container) {
//				uniform update todo

				if (renderItem.mStatus.bVAO) {
					core::bindVAO(renderItem.mHandles[RenderItem::eRenderHandleVAO]);
				}
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
				if (renderItem.mStatus.bDiffuse) {
					core::bindTexture(GL_TEXTURE_2D, aiTextureType_DIFFUSE,
					                  renderItem.mHandles[RenderItem::eRenderHandleDiffuse]);
				}

				if (renderItem.mStatus.bNormal) {
					core::bindTexture(GL_TEXTURE_2D, aiTextureType_NORMALS,
					                  renderItem.mHandles[RenderItem::eRenderHandleNormal]);
				}

				if (renderItem.mStatus.bSpecular) {
					core::bindTexture(GL_TEXTURE_2D, aiTextureType_SPECULAR,
					                  renderItem.mHandles[RenderItem::eRenderHandleSpecular]);
				}
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

				// xxx Only assimp handled
				renderItem.mStatus.bIndexDraw
				? glDrawElements(renderItem.mMode, renderItem.mCount, renderItem.mDataType,
				                 reinterpret_cast<GLvoid*>(renderItem.mIndicesPointer))
				: glDrawArrays(renderItem.mMode, renderItem.mFirst, renderItem.mCount);

				FLOG_CHECK("Draw failed");

				renderItem.mStatus.bVAO ? core::VertexArray::unbindVAO() : (void)0;

				core::Texture2D::unbind2DTextures();
			}
		}
	}
}

void IRendererCSPBRP::reset(GLuint /*width*/, GLuint /*height*/) {
	mFlagReload = true;
}

void IRendererCSPBRP::clear() {
	mFlagReload = true;
	size_t predictedSize = mRenderPasses.size() + 1;
	mRenderPasses.clear();
	mRenderPasses.reserve(predictedSize);
}

} /* namespace framework */
} /* namespace fillwave */
