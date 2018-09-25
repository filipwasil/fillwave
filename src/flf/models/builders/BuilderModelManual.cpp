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

#include <flw/flf/models/builders/BuilderModelManual.h>

namespace flw {
namespace flf {

/*! \class BuilderModelManual
 * \brief BuilderModel which builds the model from the asset file but uses external textures and meterial.
 */

BuilderModelManual::BuilderModelManual(Engine* engine,
    std::string modelPath,
    flc::Program* program,
    flc::Texture2D* diffuseMap,
    flc::Texture2D* normalMap,
    flc::Texture2D* specularMap,
    Material material)
    : BuilderModel(engine, modelPath, program)
    , mDiffuseMap(diffuseMap)
    , mNormalMap(normalMap)
    , mSpecularMap(specularMap)
    , mMaterial(material) {

}

BuilderModelManual &BuilderModelManual::setDiffuseMapTexture(flc::Texture2D* texture) {
  mDiffuseMap = texture;
  return (*this);
}

BuilderModelManual &BuilderModelManual::setNormalMapTexture(flc::Texture2D* texture) {
  mNormalMap = texture;
  return (*this);
}

BuilderModelManual &BuilderModelManual::setSpecularMapTexture(flc::Texture2D* texture) {
  mSpecularMap = texture;
  return (*this);
}

BuilderModelManual &BuilderModelManual::setMaterial(const Material& material) {
  mMaterial = material;
  return (*this);
}

pu<Model> BuilderModelManual::build() const {
  return std::make_unique<Model>(mEngine, mProgram, mShapePath, mDiffuseMap, mNormalMap, mSpecularMap, mMaterial);
}

} /* flf */
} /* flw */
