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
	   core::Program* program = nullptr,
	   core::Texture2D* diffuseMap = nullptr,
	   core::Texture2D* normalMap = nullptr,
	   core::Texture2D* specularMap = nullptr,
	   Material material = Material());

	virtual ~BuilderModelManual() = default;

	BuilderModelManual& setDiffuseMapTexture(core::Texture2D* texture);
	BuilderModelManual& setNormalMapTexture(core::Texture2D* texture);
	BuilderModelManual& setSpecularMapTexture(core::Texture2D* texture);
	BuilderModelManual& setMaterial(Material material);
	pModel build();

 private:
	core::Texture2D* mDiffuseMap;
	core::Texture2D* mNormalMap;
	core::Texture2D* mSpecularMap;
	Material mMaterial;
};

} /* framework */
} /* fillwave */

#endif /* INC_FILLWAVE_MODELS_BUILDERMODELMANUAL_H_ */
