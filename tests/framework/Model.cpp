/*
 * Model.cpp
 *
 *  Created on: Jan 17, 2016
 *      Author: filip
 */

#include <fillwave/models/Model.h>

using namespace fillwave;

pModel buildModel(
		Engine* engine,
		core::Program* program,
		framework::Shape<core::VertexBasic>& shape,
		core::Texture2D* diffuseMap,
		core::Texture2D* normalMap ,
		core::Texture2D* specularMap,
		framework::Material material) {

}

pModel buildModel(
		Engine* engine,
		core::Program* program,
		const std::string& shapePath,
		const std::string& diffuseMapPath,
		const std::string& normalMapPath,
		const std::string& specularMapPath) {

}

pModel buildModel(
		Engine* engine,
		core::Program* program,
		const std::string& shapePath,
		core::Texture2D* diffuseMap,
		core::Texture2D* normalMap,
		core::Texture2D* specularMap,
		framework::Material material) {

}

pModel buildModel(
		Engine* engine,
		core::Program* program,
		const std::string& shapePath) {

}