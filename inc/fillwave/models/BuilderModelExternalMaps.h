/*
 * BuilderModelExternalMaps.h
 *
 *  Created on: Apr 27, 2015
 *      Author: filip
 */

#ifndef INC_FILLWAVE_MODELS_BUILDERMODELEXTERNALMAPS_H_
#define INC_FILLWAVE_MODELS_BUILDERMODELEXTERNALMAPS_H_

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

#include <fillwave/models/BuilderModel.h>

namespace fillwave {
namespace models {

/*! \class BuilderModelExternalMaps
 * \brief BuilderModel which builds the model from the asset file but uses external texture maps.
 */

class BuilderModelExternalMaps: public BuilderModel {
public:
   BuilderModelExternalMaps(Engine* engine,
                            std::string modelPath = "",
                            pProgram program = pProgram(),
                            std::string diffusePath = "",
                            std::string normalPath = "",
                            std::string specularPath = "");
   virtual ~BuilderModelExternalMaps();

   BuilderModel& setdiffusePath(std::string& path);

   BuilderModel& setNormalMapPath(std::string& path);

   BuilderModel& setSpecularMapPath(std::string& path);

   pModel build();

private:
   std::string mDiffuseMapPath;
   std::string mNormalMapPath;
   std::string mSpecularMapPath;
};

} /* models */
} /* fillwave */

#endif /* INC_FILLWAVE_MODELS_BUILDERMODELEXTERNALMAPS_H_ */
