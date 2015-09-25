/*
 * BuilderModelManual.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2015] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/models/BuilderModelManual.h>

FLOGINIT("BuilderModelManual", FERROR | FFATAL)

namespace fillwave {
namespace models {

/*! \class BuilderModelManual
 * \brief BuilderModel which builds the model from the asset file but uses external textures and meterial.
 */

BuilderModelManual::BuilderModelManual(Engine* engine,
      std::string modelPath,
      pProgram program,
      pTexture diffuseMap,
      pTexture normalMap,
      pTexture specularMap,
      Material material)
:BuilderModel(engine, modelPath, program),
 mDiffuseMap(diffuseMap),
 mNormalMap(normalMap),
 mSpecularMap(specularMap),
 mMaterial(material) {

}

BuilderModelManual::~BuilderModelManual() {
}

BuilderModelManual& BuilderModelManual::setDiffuseMapTexture(pTexture texture) {
   mDiffuseMap = texture;
   return (*this);
}

BuilderModelManual& BuilderModelManual::setNormalMapTexture(pTexture texture) {
   mNormalMap = texture;
   return (*this);
}

BuilderModelManual& BuilderModelManual::setSpecularMapTexture(pTexture texture) {
   mSpecularMap = texture;
   return (*this);
}

BuilderModelManual& BuilderModelManual::setMaterial(Material material) {
   mMaterial = material;
   return (*this);
}

pModel BuilderModelManual::build() {
   return buildModel(mEngine,
              mProgram,
              mShapePath,
              mDiffuseMap,
              mNormalMap,
              mSpecularMap,
              mMaterial);
}

} /* models */
} /* fillwave */
