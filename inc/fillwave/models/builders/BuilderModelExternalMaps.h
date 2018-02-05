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

/*! \class BuilderModelExternalMaps
 * \brief BuilderModel which builds the model from the asset file but uses external texture maps.
 */

class BuilderModelExternalMaps : public BuilderModel {
public:
  BuilderModelExternalMaps(Engine *engine,
      std::string modelPath = "",
      flc::Program *program = nullptr,
      const std::string &diffusePath = "",
      const std::string &normalPath = "",
      const std::string &specularPath = "");

  virtual ~BuilderModelExternalMaps() = default;

  BuilderModel& setdiffusePath(const std::string& path);

  BuilderModel& setNormalMapPath(const std::string& path);

  BuilderModel& setSpecularMapPath(const std::string& path);

  pu<Model> build() const override;

private:
  std::string mDiffuseMapPath;
  std::string mNormalMapPath;
  std::string mSpecularMapPath;
};

} /* flf */
} /* flw */
