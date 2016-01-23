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
		pProgram program,
		framework::Shape<core::VertexBasic>& shape,
		pTexture2D diffuseMap,
		pTexture2D normalMap ,
		pTexture2D specularMap,
		framework::Material material) {

}

pModel buildModel(
		Engine* engine,
		pProgram program,
		const std::string& shapePath,
		const std::string& diffuseMapPath,
		const std::string& normalMapPath,
		const std::string& specularMapPath) {

}

pModel buildModel(
		Engine* engine,
		pProgram program,
		const std::string& shapePath,
		pTexture2D diffuseMap,
		pTexture2D normalMap,
		pTexture2D specularMap,
		framework::Material material) {

}

pModel buildModel(
		Engine* engine,
		pProgram program,
		const std::string& shapePath) {

}
