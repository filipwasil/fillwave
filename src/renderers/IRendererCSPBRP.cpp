/*
 * IRendererCSPBRP.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: filip
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

				fLogC("Draw failed");

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
