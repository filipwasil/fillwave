/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <flw/flc/renderers/mRendererCSPBRP.h>

#include <flw/flf/models/Entity.h>
#include <flw/flf/models/Skybox.h>

#include <flw/flc/texturing/Texture2D.h>

#include <flw/flf/management/LightSystem.h>

#include <flw/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flc {

RendererCSPBRP::RendererCSPBRP(flf::LightSystem* lightManager) : mLights(lightManager) {
  assert("Feature not ready");
}

void RendererCSPBRP::update(IRenderable *renderable) {
  RenderItem item;
  renderable->getRenderItem(item);
  GLuint programId = item.mHandles[RenderItem::eRenderHandleProgram];
  std::vector<RenderItem> items(1, item);
  if (mRenderPasses.find(programId) != mRenderPasses.end()) {
    mRenderPasses[programId].push_back(items);
  } else {
    std::vector<std::vector<RenderItem>> container;
    container.push_back(items);
    mRenderPasses[programId] = container;
  }
}

void RendererCSPBRP::draw(ICamera &camera) {
  //todo RendererCSPBRP is not ready
  if (mSkybox) {
    mSkybox->draw(camera);
  }
  glClear(GL_DEPTH_BUFFER_BIT);
  for (auto &program : mRenderPasses) {
    flc::Program::useProgram(program.first);
    (void) mLights;
// 	Light system supports only Fillwave programs
//    mLights->pushLightUniforms(program.first);
//		mLightManager->bindShadowmaps();
    for (auto &container : program.second) {
      // Evaluate animations
      // other stuff
      // Is Lambda fast enough ?
      for (auto &renderItem : container) {
//				uniform update

        if (renderItem.mStatus.bVAO) {
          flc::bindVAO(renderItem.mHandles[RenderItem::eRenderHandleVAO]);
        }
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
        if (renderItem.mStatus.bDiffuse) {
          flc::bindTexture(GL_TEXTURE_2D,
                            aiTextureType_DIFFUSE,
                            renderItem.mHandles[RenderItem::eRenderHandleDiffuse]);
        }

        if (renderItem.mStatus.bNormal) {
          flc::bindTexture(GL_TEXTURE_2D, aiTextureType_NORMALS, renderItem.mHandles[RenderItem::eRenderHandleNormal]);
        }

        if (renderItem.mStatus.bSpecular) {
          flc::bindTexture(GL_TEXTURE_2D,
                            aiTextureType_SPECULAR,
                            renderItem.mHandles[RenderItem::eRenderHandleSpecular]);
        }
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

        // Only assimp handled
        renderItem.mStatus.bIndexDraw ? glDrawElements(renderItem.mMode,
                                                       renderItem.mCount,
                                                       renderItem.mDataType,
                                                       reinterpret_cast<GLvoid *>(renderItem.mIndicesPointer))
                                      : glDrawArrays(renderItem.mMode, renderItem.mFirst, renderItem.mCount);

        fLogC("Draw failed");

        renderItem.mStatus.bVAO ? flc::VertexArray::unbindVAO() : (void) 0;

        flc::Texture2D::unbind2DTextures();
      }
    }
  }
}

void RendererCSPBRP::reset(GLuint /*width*/, GLuint /*height*/) {
  mFlagReload = true;
}

void RendererCSPBRP::clear() {
  mFlagReload = true;
  size_t predictedSize = mRenderPasses.size() + 1;
  mRenderPasses.clear();
  mRenderPasses.reserve(predictedSize);
}

} /* flc */
} /* flf */
