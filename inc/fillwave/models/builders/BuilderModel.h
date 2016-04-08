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
	BuilderModel(Engine* engine, std::string modelPath, pProgram program);

	virtual ~BuilderModel() = default;

	virtual pModel build();

	BuilderModel& setModelPath(std::string& path);
	BuilderModel& setProgram(pProgram program);

  protected:
	Engine* mEngine;
	pProgram mProgram;
	std::string mShapePath;
};

} /* framework */
} /* fillwave */

#endif /* INC_FILLWAVE_MODELS_BUILDERMODEL_H_ */
