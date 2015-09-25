/*
 * Material.cpp
 *
 *  Created on: 27 sty 2015
 *      Author: filip
 */

#include <fillwave/models/Material.h>
#include <fillwave/extras/Conversion.h>

namespace fillwave {
namespace models {

Material::Material() {
   mAmbient = glm::vec4(0.1,0.1,0.1,1.0);
   mDiffuse = glm::vec4(1.0);
   mSpecular = glm::vec4(1.0);
}


Material::Material(const aiMaterial* material) {
   aiColor4D color;
   if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &color)) {
      mAmbient = assimpToGlmVec4(color);
   }
   if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color)) {
      mDiffuse = assimpToGlmVec4(color);
   }
   if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color)) {
      mSpecular = assimpToGlmVec4(color);
   }
}

Material::~Material() {

}

glm::vec4 Material::getAmbient() {
   return mAmbient;
}

glm::vec4 Material::getDiffuse() {
   return mDiffuse;
}

glm::vec4 Material::getSpecular() {
   return mSpecular;
}

} /* models */
} /* fillwave */
