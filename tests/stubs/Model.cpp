/*
 * Model.cpp
 *
 *  Created on: Jan 17, 2016
 *      Author: filip
 */

#include <fillwave/models/Model.h>

using namespace fillwave;

pModel buildModel(
   Engine*,
   core::Program*,
   framework::Shape<core::VertexBasic>&,
   core::Texture2D*,
   core::Texture2D*,
   core::Texture2D*,
   framework::Material) {
	return pModel();
}

pModel buildModel(
   Engine*,
   core::Program*,
   const std::string&,
   const std::string&,
   const std::string&,
   const std::string&) {
	return pModel();
}

pModel buildModel(
   Engine*,
   core::Program*,
   const std::string&,
   core::Texture2D*,
   core::Texture2D*,
   core::Texture2D*,
   framework::Material) {
	return pModel();
}

pModel buildModel(
   Engine*,
   core::Program*,
   const std::string&) {
	return pModel();
}
