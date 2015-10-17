/*
 * BuilderModelManual.h
 *
 *  Created on: Apr 27, 2015
 *      Author: Filip Wasil
 */

#ifndef INC_FILLWAVE_MODELS_BUILDERMODELMANUAL_H_
#define INC_FILLWAVE_MODELS_BUILDERMODELMANUAL_H_

#include <fillwave/models/BuilderModel.h>

namespace fillwave {
namespace models {

/*! \class BuilderModelManual
 * \brief BuilderModel which builds the model from textures and material fillwave objects.
 */

class BuilderModelManual: public BuilderModel {
public:
	BuilderModelManual(
			Engine* engine,
			std::string modelPath = "",
			pProgram program = pProgram(),
			pTexture diffuseMap = pTexture(),
			pTexture normalMap = pTexture(),
			pTexture specularMap = pTexture(),
			Material material = Material());

	virtual ~BuilderModelManual() = default;

	BuilderModelManual& setDiffuseMapTexture(pTexture texture);

	BuilderModelManual& setNormalMapTexture(pTexture texture);

	BuilderModelManual& setSpecularMapTexture(pTexture texture);

	BuilderModelManual& setMaterial(Material material);

	pModel build();

private:
	pTexture mDiffuseMap;
	pTexture mNormalMap;
	pTexture mSpecularMap;
	Material mMaterial;
};

} /* models */
} /* fillwave */

#endif /* INC_FILLWAVE_MODELS_BUILDERMODELMANUAL_H_ */
