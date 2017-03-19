/*
 * BuilderModelManual.cpp
 *
 *  Created on: Apr 27, 2015
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


#include <fillwave/models/builders/BuilderModelManual.h>
#include <fillwave/Log.h>


namespace fillwave {
namespace framework {

/*! \class BuilderModelManual
 * \brief BuilderModel which builds the model from the asset file but uses external textures and meterial.
 */

BuilderModelManual::BuilderModelManual(Engine *engine,
    std::string modelPath,
    core::Program *program,
    core::Texture2D *diffuseMap,
    core::Texture2D *normalMap,
    core::Texture2D *specularMap,
    Material material)
    : BuilderModel(engine, modelPath, program), mDiffuseMap(diffuseMap), mNormalMap(normalMap)
    , mSpecularMap(specularMap), mMaterial(material) {

}

BuilderModelManual &BuilderModelManual::setDiffuseMapTexture(core::Texture2D *texture) {
  mDiffuseMap = texture;
  return (*this);
}

BuilderModelManual &BuilderModelManual::setNormalMapTexture(core::Texture2D *texture) {
  mNormalMap = texture;
  return (*this);
}

BuilderModelManual &BuilderModelManual::setSpecularMapTexture(core::Texture2D *texture) {
  mSpecularMap = texture;
  return (*this);
}

BuilderModelManual &BuilderModelManual::setMaterial(const Material &material) {
  mMaterial = material;
  return (*this);
}

puModel BuilderModelManual::build() {
  return std::make_unique<Model>(mEngine, mProgram, mShapePath, mDiffuseMap, mNormalMap, mSpecularMap, mMaterial);
}

} /* framework */
} /* fillwave */
