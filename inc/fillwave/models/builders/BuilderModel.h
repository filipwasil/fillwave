/*
 * BuilderModel.h
 *
 *  Created on: Apr 26, 2015
 *      Author: Filip Wasil
 */

#ifndef INC_FILLWAVE_MODELS_BUILDERMODEL_H_
#define INC_FILLWAVE_MODELS_BUILDERMODEL_H_

#include <fillwave/models/Model.h>

namespace fillwave {
class Engine;
namespace framework {

/*! \class BuilderModel
 * \brief Builder which builds the model from the asset file.
 */

class BuilderModel {
 public:
	BuilderModel(Engine* engine, std::string modelPath, core::Program* program);

	virtual ~BuilderModel() = default;

	virtual puModel build();

	BuilderModel& setModelPath(std::string& path);
	BuilderModel& setProgram(core::Program* program);

 protected:
	Engine* mEngine;
	core::Program* mProgram;
	std::string mShapePath;
};

} /* framework */
} /* fillwave */

#endif /* INC_FILLWAVE_MODELS_BUILDERMODEL_H_ */
