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

#include <flw/flf/models/builders/BuilderModelExternalMaps.h>

namespace flw {
namespace flf {

BuilderModelExternalMaps::BuilderModelExternalMaps(Engine* engine,
    std::string modelPath,
    flc::Program* program,
    const std::string& diffusePath,
    const std::string& normalPath,
    const std::string& specularPath)
    : BuilderModel(engine, modelPath, program)
    , mDiffuseMapPath(diffusePath)
    , mNormalMapPath(normalPath)
    , mSpecularMapPath(specularPath) {

}

BuilderModel &BuilderModelExternalMaps::setdiffusePath(const std::string& path) {
  mDiffuseMapPath = path;
  return *this;
}

BuilderModel &BuilderModelExternalMaps::setNormalMapPath(const std::string& path) {
  mNormalMapPath = path;
  return *this;
}

BuilderModel &BuilderModelExternalMaps::setSpecularMapPath(const std::string& path) {
  mSpecularMapPath = path;
  return *this;
}

pu<Model> BuilderModelExternalMaps::build() const {
  return std::make_unique<Model>(mEngine, mProgram, mShapePath, mDiffuseMapPath, mNormalMapPath, mSpecularMapPath);
}

} /* flf */
} /* flw */

