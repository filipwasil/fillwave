/*
 * BuilderModelManual.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: filip
 */

#include <fillwave/models/builders/BuilderModelManual.h>
#include <fillwave/common/Macros.h>
#include <fillwave/Log.h>

FLOGINIT("BuilderModelManual", FERROR | FFATAL)

namespace fillwave {
namespace framework {

/*! \class BuilderModelManual
 * \brief BuilderModel which builds the model from the asset file but uses external textures and meterial.
 */

BuilderModelManual::BuilderModelManual(
   Engine* engine,
   std::string modelPath,
   core::Program* program,
   core::Texture2D* diffuseMap,
   core::Texture2D* normalMap,
   core::Texture2D* specularMap,
   Material material) :
	BuilderModel(engine, modelPath, program),
	mDiffuseMap(diffuseMap),
	mNormalMap(normalMap),
	mSpecularMap(specularMap),
	mMaterial(material) {

}

BuilderModelManual& BuilderModelManual::setDiffuseMapTexture(
   core::Texture2D* texture) {
	mDiffuseMap = texture;
	return (*this);
}

BuilderModelManual& BuilderModelManual::setNormalMapTexture(
   core::Texture2D* texture) {
	mNormalMap = texture;
	return (*this);
}

BuilderModelManual& BuilderModelManual::setSpecularMapTexture(
   core::Texture2D* texture) {
	mSpecularMap = texture;
	return (*this);
}

BuilderModelManual& BuilderModelManual::setMaterial(Material material) {
	mMaterial = material;
	return (*this);
}

puModel BuilderModelManual::build() {
	return std::make_unique<Model>(mEngine, mProgram, mShapePath, mDiffuseMap,
	                               mNormalMap,
	                               mSpecularMap, mMaterial);
}

} /* framework */
} /* fillwave */
