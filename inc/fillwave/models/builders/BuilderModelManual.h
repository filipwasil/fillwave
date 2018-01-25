#pragma once

/*
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

#include <fillwave/models/builders/BuilderModel.h>

namespace flw {
namespace flf {

/*! \class BuilderModelManual
 * \brief BuilderModel which builds the model from textures and material fillwave objects.
 */

class BuilderModelManual : public BuilderModel {
public:
  BuilderModelManual(Engine *engine,
      std::string modelPath = "",
      flc::Program *program = nullptr,
      flc::Texture2D *diffuseMap = nullptr,
      flc::Texture2D *normalMap = nullptr,
      flc::Texture2D *specularMap = nullptr,
      Material material = Material());

  virtual ~BuilderModelManual() = default;

  BuilderModelManual &setDiffuseMapTexture(flc::Texture2D *texture);

  BuilderModelManual &setNormalMapTexture(flc::Texture2D *texture);

  BuilderModelManual &setSpecularMapTexture(flc::Texture2D *texture);

  BuilderModelManual &setMaterial(const Material &material);

  pu<Model> build();

private:
  flc::Texture2D *mDiffuseMap;
  flc::Texture2D *mNormalMap;
  flc::Texture2D *mSpecularMap;
  Material mMaterial;
};

} /* flf */
} /* flw */
