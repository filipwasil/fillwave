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

#include <flw/flf/models/MeshTerrain.h>
#include <flw/flf/loaders/ProgramLoader.h>
#include <flw/flf/management/LightSystem.h>

#include <flw/Fillwave.h>

namespace flw {
namespace flf {

// todo code duplication in constructors
MeshTerrain::MeshTerrain(Engine *engine,
  flc::Program *program,
  std::function<float(float x, float y)> constructor,
  const Material & /*material*/, //xxx to be used
  const std::string &diffuseMapPath,
  const std::string &normalMapPath,
  const std::string &specularMapPath,
  GLuint radius,
  GLuint density)
  : Programmable(program)
  , mLights(engine->getLightSystem())
  , mJumpStep(density * 0.2f * 16.0f / density) {

  std::vector<GLuint> indices;

  initIBO(indices, density);

  GLfloat gapSize = 0.2f * 16.0f / density;
  GLint indexTerrainChunk = radius;
  ProgramLoader loader(engine);

  auto vao = new flc::VertexArray();
  auto vbo = engine->storeBuffer<flc::VertexBufferBasic>(vao, constructor, density, gapSize, indices);
  auto ibo = engine->storeBuffer<flc::IndexBuffer>(vao, indices);

  Material m;

  for (GLint x = -indexTerrainChunk; x <= indexTerrainChunk; ++x) {
    for (GLint z = -indexTerrainChunk; z <= indexTerrainChunk; ++z) {
      auto ptr = std::make_unique<Mesh>(
        engine
        , m
        , engine->storeTexture(diffuseMapPath.c_str())
        , engine->storeTexture(normalMapPath.c_str())
        , engine->storeTexture(specularMapPath.c_str())
        , program
        , loader.getProgram(EProgram::shadow)
        , loader.getProgram(EProgram::shadowColorCoded)
        , loader.getProgram(EProgram::occlusionOptimizedQuery)
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
        , nullptr
#else
        , loader.getProgram(EProgram::ambientOcclusionGeometry)
#endif
        , loader.getProgram(EProgram::ambientOcclusionColor)
        , engine->getLightSystem()
        , vbo
        , ibo
        , nullptr
        , GL_TRIANGLES
        , vao);

      ptr->moveTo(glm::vec3(density * gapSize * (GLfloat(x)), 0.0, density * gapSize * (GLfloat(z))));

      attach(std::move(ptr));
    }
  }
}

//xxx code duplication in constructors. fix
MeshTerrain::MeshTerrain(Engine *engine,
    flc::Program *program,
    std::function<float(float x, float y)> constructor,
    const Material& /*material*/, //xxx to be used
    flc::Texture2D* diffuseMap,
    flc::Texture2D* normalMap,
    flc::Texture2D* specularMap,
    GLuint radius,
    GLuint density)
    : Programmable(program)
    , mLights(engine->getLightSystem())
    , mJumpStep(density * 0.2f * 16.0f / density) {

  std::vector<GLuint> indices;

  initIBO(indices, density);

  GLfloat gapSize = 0.2f * 16.0f / density;
  GLint indexTerrainChunk = radius;
  ProgramLoader loader(engine);

  auto vao = new flc::VertexArray();
  auto vbo = engine->storeBuffer<flc::VertexBufferBasic>(vao, constructor, density, gapSize, indices);
  auto ibo = engine->storeBuffer<flc::IndexBuffer>(vao, indices);

  for (GLint x = -indexTerrainChunk; x <= indexTerrainChunk; ++x) {
    for (GLint z = -indexTerrainChunk; z <= indexTerrainChunk; ++z) {
      pu<Mesh> ptr = std::make_unique<Mesh>(engine,
                                          Material(),
                                          diffuseMap,
                                          normalMap,
                                          specularMap,
                                          program,
                                          loader.getProgram(EProgram::shadow),
                                          loader.getProgram(EProgram::shadowColorCoded),
                                          loader.getProgram(EProgram::occlusionOptimizedQuery),
                                          loader.getProgram(EProgram::ambientOcclusionGeometry),
                                          loader.getProgram(EProgram::ambientOcclusionColor),
                                          engine->getLightSystem(),
                                          vbo,
                                          ibo,
                                          nullptr,
                                          GL_TRIANGLES,
                                          vao);

      ptr->moveTo(glm::vec3(density * gapSize * (GLfloat(x)), 0.0, density * gapSize * (GLfloat(z))));
      attach(std::move(ptr));
    }
  }
}

void MeshTerrain::initIBO(std::vector<GLuint> &indices, GLuint density) {
  int pointsWidth, pointsWidthNext, offset;

  indices.reserve(density * density);

  for (GLuint z = 0; z < density; ++z) {
    for (GLuint x = 0; x < density; ++x) {
      pointsWidth = density + 1;
      pointsWidthNext = density + 2;
      offset = x + z * pointsWidth;
      indices.push_back(0 + offset);
      indices.push_back(pointsWidth + offset);
      indices.push_back(pointsWidthNext + offset);
      indices.push_back(1 + offset);
      indices.push_back(0 + offset);
      indices.push_back(pointsWidthNext + offset);
    }
  }
}

void MeshTerrain::draw(ICamera &camera) {
  distanceCheck(camera);
  drawWithEffects(camera);
}

void MeshTerrain::drawPBRP(ICamera &camera) {
  distanceCheck(camera);
  mLights.pushLightUniforms(mProgram);
  mLights.bindShadowmaps();
  for (auto &it : mChildren) {
    it->drawPBRP(camera);
  }
}

void MeshTerrain::updateRenderer(IRenderer &renderer) {
  renderer.update(this);
}

inline void MeshTerrain::distanceCheck(ICamera &camera) {
  /* check if there are any children too far away from the camera */
  const glm::vec3 distanceToCamera = camera.getTranslation() - getTranslation();
  const GLfloat maximumDistance = mJumpStep * 2;
  const GLfloat jumpStep = mJumpStep * 2;

  if (glm::abs(distanceToCamera.x) > maximumDistance) {
    moveByX( ( distanceToCamera.x > 0.0f ? 1.0f : -1.0f ) * jumpStep);
  }
  if (glm::abs(distanceToCamera.z) > maximumDistance) {
    moveByZ( ( distanceToCamera.z > 0.0f ? 1.0f : -1.0f ) * jumpStep);
  }
}

} /* flf */
} /* flw */
