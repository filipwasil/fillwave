/*
 * BuilderModelExternalMaps.h
 *
 *  Created on: Apr 27, 2015
 *      Author: filip
 */

#ifndef INC_FILLWAVE_MODELS_BUILDERMODELEXTERNALMAPS_H_
#define INC_FILLWAVE_MODELS_BUILDERMODELEXTERNALMAPS_H_

#include <fillwave/models/builders/BuilderModel.h>

namespace fillwave {
namespace framework {

/*! \class BuilderModelExternalMaps
 * \brief BuilderModel which builds the model from the asset file but uses external texture maps.
 */

class BuilderModelExternalMaps: public BuilderModel {
public:
	BuilderModelExternalMaps(
			Engine* engine,
			std::string modelPath = "",
			pProgram program = pProgram(),
			std::string diffusePath = "",
			std::string normalPath = "",
			std::string specularPath = "");
	virtual ~BuilderModelExternalMaps() = default;

	BuilderModel& setdiffusePath(std::string& path);
	BuilderModel& setNormalMapPath(std::string& path);
	BuilderModel& setSpecularMapPath(std::string& path);
	pModel build();

private:
	std::string mDiffuseMapPath;
	std::string mNormalMapPath;
	std::string mSpecularMapPath;
};

} /* framework */
} /* fillwave */

#endif /* INC_FILLWAVE_MODELS_BUILDERMODELEXTERNALMAPS_H_ */
