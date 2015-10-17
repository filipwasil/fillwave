/*
 * BuilderModelManual.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: filip
 */

#include <fillwave/models/BuilderModelManual.h>

FLOGINIT("BuilderModelManual", FERROR | FFATAL)

namespace fillwave {
namespace models {

/*! \class BuilderModelManual
 * \brief BuilderModel which builds the model from the asset file but uses external textures and meterial.
 */

BuilderModelManual::BuilderModelManual(
		Engine* engine,
		std::string modelPath,
		pProgram program,
		pTexture diffuseMap,
		pTexture normalMap,
		pTexture specularMap,
		Material material)
		:
				BuilderModel(engine, modelPath, program),
				mDiffuseMap(diffuseMap),
				mNormalMap(normalMap),
				mSpecularMap(specularMap),
				mMaterial(material) {

}

BuilderModelManual& BuilderModelManual::setDiffuseMapTexture(pTexture texture) {
	mDiffuseMap = texture;
	return (*this);
}

BuilderModelManual& BuilderModelManual::setNormalMapTexture(pTexture texture) {
	mNormalMap = texture;
	return (*this);
}

BuilderModelManual& BuilderModelManual::setSpecularMapTexture(
		pTexture texture) {
	mSpecularMap = texture;
	return (*this);
}

BuilderModelManual& BuilderModelManual::setMaterial(Material material) {
	mMaterial = material;
	return (*this);
}

pModel BuilderModelManual::build() {
	return buildModel(mEngine, mProgram, mShapePath, mDiffuseMap, mNormalMap,
			mSpecularMap, mMaterial);
}

} /* models */
} /* fillwave */
