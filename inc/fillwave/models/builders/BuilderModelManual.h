/*
 * BuilderModelManual.h
 *
 *  Created on: Apr 27, 2015
 *      Author: Filip Wasil
 */

#ifndef INC_FILLWAVE_MODELS_BUILDERMODELMANUAL_H_
#define INC_FILLWAVE_MODELS_BUILDERMODELMANUAL_H_

#include <fillwave/models/builders/BuilderModel.h>

namespace fillwave {
namespace framework {

/*! \class BuilderModelManual
 * \brief BuilderModel which builds the model from textures and material fillwave objects.
 */

class BuilderModelManual: public BuilderModel {
public:
	BuilderModelManual(
			Engine* engine,
			std::string modelPath = "",
			pProgram program = pProgram(),
			pTexture2D diffuseMap = pTexture2D(),
			pTexture2D normalMap = pTexture2D(),
			pTexture2D specularMap = pTexture2D(),
			Material material = Material());

	virtual ~BuilderModelManual() = default;

	BuilderModelManual& setDiffuseMapTexture(pTexture2D texture);
	BuilderModelManual& setNormalMapTexture(pTexture2D texture);
	BuilderModelManual& setSpecularMapTexture(pTexture2D texture);
	BuilderModelManual& setMaterial(Material material);
	pModel build();

private:
	pTexture2D mDiffuseMap;
	pTexture2D mNormalMap;
	pTexture2D mSpecularMap;
	Material mMaterial;
};

} /* framework */
} /* fillwave */

#endif /* INC_FILLWAVE_MODELS_BUILDERMODELMANUAL_H_ */
