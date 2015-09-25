/*
 * BuilderModel.h
 *
 *  Created on: Apr 26, 2015
 *      Author: Filip Wasil
 */

#ifndef INC_FILLWAVE_MODELS_BUILDERMODEL_H_
#define INC_FILLWAVE_MODELS_BUILDERMODEL_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/models/Model.h>

namespace fillwave {

class Engine;

namespace models {

/*! \class BuilderModel
 * \brief Builder which builds the model from the asset file.
 */

class BuilderModel {
public:
	BuilderModel(Engine* engine, std::string modelPath, pProgram program);

	virtual ~BuilderModel();

	virtual pModel build();

	BuilderModel& setModelPath(std::string& path);

	BuilderModel& setProgram(pProgram program);

protected:
	Engine* mEngine;
	pProgram mProgram;
	std::string mShapePath;
};

} /* models */
} /* fillwave */

#endif /* INC_FILLWAVE_MODELS_BUILDERMODEL_H_ */
