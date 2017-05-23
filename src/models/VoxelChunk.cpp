/*
 * VoxelChunk.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: filip
 *
 * Copyright (c) 2017, Fillwave developers
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


#include <fillwave/models/terrain/VoxelChunk.h>
#include <fillwave/Fillwave.h>
#include <fillwave/management/LightSystem.h>
#include <fillwave/Log.h>

FLOGINIT("VoxelChunk", FERROR | FFATAL)

namespace flw {
namespace flf {

const GLfloat voxelPositions[] = {
    0.10000f,
    -0.10000f,
    0.10000f,
    -0.10000f,
    -0.10000f,
    0.10000f,
    -0.10000f,
    -0.10000f,
    -0.10000f,
    -0.10000f,
    0.10000f,
    -0.10000f,
    -0.10000f,
    0.10000f,
    0.10000f,
    0.10000f,
    0.10000f,
    0.10000f,
    0.10000f,
    -0.10000f,
    -0.10000f,
    0.10000f,
    0.10000f,
    -0.10000f,
    0.10000f,
    0.10000f,
    0.10000f,
    0.10000f,
    -0.10000f,
    0.10000f,
    0.10000f,
    0.10000f,
    0.10000f,
    -0.10000f,
    0.10000f,
    0.10000f,
    -0.10000f,
    0.10000f,
    0.10000f,
    -0.10000f,
    0.10000f,
    -0.10000f,
    -0.10000f,
    -0.10000f,
    -0.10000f,
    0.10000f,
    -0.10000f,
    -0.10000f,
    -0.10000f,
    -0.10000f,
    -0.10000f,
    -0.10000f,
    0.10000f,
    -0.10000f,
    0.10000f,
    -0.10000f,
    -0.10000f,
    0.10000f,
    -0.10000f,
    0.10000f,
    -0.10000f,
    -0.10000f,
    -0.10000f,
    0.10000f,
    0.10000f,
    -0.10000f,
    -0.10000f,
    0.10000f,
    -0.10000f,
    0.10000f,
    0.10000f,
    0.10000f,
    0.10000f,
    -0.10000f,
    0.10000f,
    0.10000f,
    -0.10000f,
    -0.10000f,
    0.10000f,
    0.10000f,
    0.10000f,
    -0.10000f,
    -0.10000f,
    0.10000f,
    0.10000f,
    -0.10000f,
    0.10000f,
    -0.10000f,
    0.10000f,
    0.10000f,
    -0.10000f,
    -0.10000f,
    0.10000f,
    -0.10000f,
    0.10000f,
    0.10000f,
    -0.10000f,
    -0.10000f,
    -0.10000f,
    0.10000f,
    0.10000f,
    -0.10000f,
    0.10000f,
    -0.10000f,
    -0.10000f,
    -0.10000f,
    0.10000f,
    -0.10000f
};

const GLfloat voxelNormals[] = {
    0.0f,
    -1.0f,
    0.0f, //-y
    0.0f,
    -1.0f,
    0.0f,
    0.0f,
    -1.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f, //+y
    0.0f,
    1.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    1.0f,
    0.0f,
    0.0f, //+x
    1.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    1.0f, //+z
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    0.0f,
    1.0f,
    -1.0f,
    0.0f,
    0.0f, //-x
    -1.0f,
    0.0f,
    0.0f,
    -1.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    -1.0f, //-z
    0.0f,
    0.0f,
    -1.0f,
    0.0f,
    0.0f,
    -1.0f,
    0.0f,
    -1.0f,
    0.0f, //-y
    0.0f,
    -1.0f,
    0.0f,
    0.0f,
    -1.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f, //+y
    0.0f,
    1.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    1.0f,
    0.0f,
    0.0f, //+x
    1.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    1.0f, //+z
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    0.0f,
    1.0f,
    -1.0f,
    0.0f,
    0.0f, //-x
    -1.0f,
    0.0f,
    0.0f,
    -1.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    -1.0f, //-z
    0.0f,
    0.0f,
    -1.0f,
    0.0f,
    0.0f,
    -1.0
};

const GLfloat voxelUV[] = {
    0.333333f,
    0.666667f,
    0.333333f,
    1.000000f,
    0.000000f,
    1.000000f,
    0.666667f,
    0.666667f,

    0.333333f,
    0.666667f,
    0.333333f,
    0.333333f,
    0.666667f,
    0.333333f,
    0.333333f,
    0.333333f,

    0.333333f,
    0.000000f,
    0.000000f,
    0.333333f,
    0.000000f,
    0.000000f,
    0.333333f,
    0.000000f,

    0.666667f,
    0.333333f,
    0.666667f,
    0.000000f,
    1.000000f,
    0.000000f,
    0.333333f,
    0.333333f,

    0.333333f,
    0.666667f,
    0.000000f,
    0.666667f,
    0.000000f,
    0.666667f,
    0.333333f,
    0.666667f,

    0.000000f,
    1.000000f,
    0.666667f,
    0.333333f,
    0.666667f,
    0.666667f,
    0.333333f,
    0.333333f,

    0.666667f,
    0.000000f,
    0.666667f,
    0.333333f,
    0.333333f,
    0.000000f,
    0.333333f,
    0.333333f,

    0.000000f,
    0.333333f,
    0.333333f,
    0.000000f,
    1.000000f,
    0.333333f,
    0.666667f,
    0.333333f,

    1.000000f,
    0.000000f,
    0.000000f,
    0.333333f,
    0.333333f,
    0.333333f,
    0.000000f,
    0.666667f
};

VoxelChunk::VoxelChunk(flc::Program *program,
    Engine *engine,
    const std::string &texturePath,
    GLint size,
    VoxelConstructor *constructor,
    GLfloat gap)
    : IReloadable(engine)
    , mEngine(engine)
    , mVoxelGap(gap)
    , mSize(size)
    , mProgram(program)
    , mTexture(engine->storeTexture(texturePath.c_str()))
    , mLights(engine->getLightSystem()) {

  mVoxels = new Voxel **[mSize];
  std::vector<flc::VertexBasic> vertices;
  vertices.reserve(mSize * mSize * mSize * 36);
  for (GLint x = 0; x < mSize; x++) {
    mVoxels[x] = new Voxel *[mSize];
    for (GLint z = 0; z < mSize; z++) {
      mVoxels[x][z] = new Voxel[mSize];
      for (GLint y = 0; y < mSize; y++) {
        GLboolean active = constructor ? constructor->calculateActiveVoxel((GLfloat) x / (GLfloat) ((mSize - 1)),
                                                                           (GLfloat) z / (GLfloat) ((mSize - 1)),
                                                                           (GLfloat) y / (GLfloat) ((mSize - 1)))
                                       : GL_TRUE;
        mVoxels[x][z][y].setActive(active);
        if (mVoxels[x][z][y].isActive()) {
          flc::VertexBasic v;
          for (GLint i = 0; i < 36; i++) {
            v.mPosition[0] = voxelPositions[3 * i] + mVoxelGap * (GLfloat) x - (GLfloat) mVoxelGap * (mSize - 1) / 2.0f;
            v.mPosition[1] = voxelPositions[3 * i + 1] + mVoxelGap * (GLfloat) y -
                             (GLfloat) mVoxelGap * (mSize - 1) / 2.0f;
            v.mPosition[2] = voxelPositions[3 * i + 2] + mVoxelGap * (GLfloat) z -
                             (GLfloat) mVoxelGap * (mSize - 1) / 2.0f;
            v.mPosition[3] = 1.0;
            v.mNormal[0] = voxelNormals[3 * i];
            v.mNormal[1] = voxelNormals[3 * i + 1];
            v.mNormal[2] = voxelNormals[3 * i + 2];
            v.mTextureUV[0] = voxelUV[2 * i];
            v.mTextureUV[1] = voxelUV[2 * i + 1];
            vertices.push_back(v);
          }
        }
      }
    }
  }
  mVBO = engine->storeBuffer<flc::VertexBufferBasic>(mVAO, vertices);

  initPipeline();
  initVBO();
  initVAO();
  initUniformsCache();
}

VoxelChunk::~VoxelChunk() {
  for (GLint x = 0; x < mSize; x++) {
    for (GLint z = 0; z < mSize; z++) {
      delete[] mVoxels[x][z];
    }
    delete[] mVoxels[x];
  }
  delete[] mVoxels;
}

void VoxelChunk::setType(GLint type) {
  for (GLint x = 0; x < mSize; x++) {
    for (GLint z = 0; z < mSize; z++) {
      for (GLint y = 0; z < mSize; y++) {
        mVoxels[x][z][y].setType(type);
      }
    }
  }
}

void VoxelChunk::reloadVBO() {

  std::vector<flc::VertexBasic> vertices;
  for (GLint x = 0; x < mSize; x++) {
    mVoxels[x] = new Voxel *[mSize];
    for (GLint z = 0; z < mSize; z++) {
      mVoxels[x][z] = new Voxel[mSize];
      for (GLint y = 0; y < mSize; y++) {
        if (mVoxels[x][z][y].isActive()) {
          flc::VertexBasic v;
          for (GLint i = 0; i < 36; i++) {
            v.mPosition[0] = voxelPositions[3 * i] + mVoxelGap * (GLfloat) x - (GLfloat) (mSize - 1) / 2.0f;
            v.mPosition[1] = voxelPositions[3 * i + 1] + mVoxelGap * (GLfloat) y - (GLfloat) (mSize - 1) / 2.0f;
            v.mPosition[2] = voxelPositions[3 * i + 2] + mVoxelGap * (GLfloat) z - (GLfloat) (mSize - 1) / 2.0f;
            v.mPosition[3] = 1.0;
            v.mNormal[0] = voxelNormals[3 * i];
            v.mNormal[1] = voxelNormals[3 * i + 1];
            v.mNormal[2] = voxelNormals[3 * i + 2];
            v.mTextureUV[0] = voxelUV[2 * i];
            v.mTextureUV[1] = voxelUV[2 * i + 1];
            vertices.push_back(v);
          }
        }
      }
    }
  }

  mVBO = mEngine->storeBuffer<flc::VertexBufferBasic>(mVAO, vertices);

  initVBO();

  initVAO();
}

void VoxelChunk::reloadVoxels(VoxelConstructor *constructor) {
  std::vector<flc::VertexBasic> vertices;
  vertices.reserve(mSize * mSize * mSize);
  for (GLint x = 0; x < mSize; x++) {
    for (GLint z = 0; z < mSize; z++) {
      for (GLint y = 0; y < mSize; y++) {
        mVoxels[x][z][y].setActive(constructor->calculateActiveVoxel((GLfloat) x / (GLfloat) mSize,
                                                                     (GLfloat) z / (GLfloat) mSize,
                                                                     (GLfloat) y / (GLfloat) mSize));
      }
    }
  }
  reloadVBO();
}

void VoxelChunk::draw(ICamera &camera) {
  mProgram->use();

  flc::Uniform::push(mUniformLocationCacheModelMatrix, mPhysicsMMC);
  flc::Uniform::push(mUniformLocationCacheCameraPosition, camera.getTranslation());
  flc::Uniform::push(mUniformLocationCacheViewProjectionMatrix, camera.getViewProjection());

  mLights.pushLightUniforms(mProgram);
  mLights.bindShadowmaps();

  mVAO->bind();

  coreDraw();

  flc::VertexArray::unbindVAO();

  flc::Program::disusePrograms();
}

void VoxelChunk::drawPBRP(ICamera &camera) {
  flc::Uniform::push(mUniformLocationCacheModelMatrix, mPhysicsMMC);
  flc::Uniform::push(mUniformLocationCacheCameraPosition, camera.getTranslation());
  flc::Uniform::push(mUniformLocationCacheViewProjectionMatrix, camera.getViewProjection());

  mVAO->bind();

  coreDraw();

  flc::VertexArray::unbindVAO();
}

GLint VoxelChunk::getSize() {
  return mSize;
}

inline void VoxelChunk::coreDraw() {
  if (mTexture) {
    mTexture->bind();
  }

  onDraw();

  flc::Texture2D::unbind2DTextures();
}

inline void VoxelChunk::onDraw() {
  glDrawArrays(GL_TRIANGLES, 0, mVBO->getElements());
  fLogC("Could not draw");
}

inline void VoxelChunk::initBuffers() {
  if (mVBO) {
    mVBO->reload();
  }
}

inline void VoxelChunk::initPipeline() {

}

inline void VoxelChunk::initUniformsCache() {
  mUniformLocationCacheModelMatrix = mProgram->getUniformLocation("uModelMatrix");
  mUniformLocationCacheCameraPosition = mProgram->getUniformLocation("uCameraPosition");
  mUniformLocationCacheViewProjectionMatrix = mProgram->getUniformLocation("uViewProjectionMatrix");
}

inline void VoxelChunk::initVAO() {
  mSampler->bind();
  mVAO->bind();

  mVBO->bind();
  mVBO->attributesSetForVAO();
  mVBO->setLoaded(GL_FALSE);
  mVBO->send();

  flc::VertexArray::unbindVAO();
}

inline void VoxelChunk::initVBO() {
  mVBO->initAttributes(mProgram->getHandle());
}

void VoxelChunk::updateRenderer(IRenderer &renderer) {
  renderer.update(this);
}

bool VoxelChunk::getRenderItem(RenderItem &item) {
  item.mCount = mVBO->getElements();
  item.mFirst = 0;
  item.mHandles[RenderItem::eRenderHandleProgram] = mProgram->getHandle();
  item.mHandles[RenderItem::eRenderHandleSampler] = mSampler->getHandle();
  item.mHandles[RenderItem::eRenderHandleVAO] = mVAO->getHandle();
  item.mHandles[RenderItem::eRenderHandleDiffuse] = mTexture->getHandle();
  item.mMode = GL_TRIANGLES;
  item.mRenderStatus = 0xc0;
  return true;
}

} /* flf */
} /* fillwave*/
