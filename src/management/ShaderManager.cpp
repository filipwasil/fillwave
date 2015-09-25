/*
 * ShaderManager.cpp
 *
 *  Created on: Apr 17, 2014
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * filip.wasil@gmail.com
 *
 */

#include <fillwave/management/ShaderManager.h>
#include <fillwave/Fillwave.h>

FLOGINIT("ShaderManager", FERROR | FFATAL)

namespace fillwave {
namespace manager {

ShaderManager::ShaderManager(const std::string& rootPath)
		: mRootPath(rootPath) {

}

ShaderManager::~ShaderManager() {

}

pShader ShaderManager::add(
		const std::string& shaderPath,
		const unsigned int shaderType) {
	for (auto& it : mShaderObjects) {
		if (it->mFilePath == shaderPath) {
			return it->mShader;
		}
	}
	puShaderObject shaderObject = puShaderObject(new ShaderObject());
	shaderObject->mFilePath = mRootPath + shaderPath;
	std::string shaderSource = "";
	loader::ReadFile(shaderObject->mFilePath, shaderSource);
	const unsigned int type = shaderType;
	shaderObject->mShader = pShader(new core::Shader(type, shaderSource));
	mShaderObjects.push_back(std::move(shaderObject));
	return mShaderObjects.back()->mShader;
}

pShader ShaderManager::add(
		const std::string& shaderName,
		const int shaderType,
		const std::string& shaderSource) {
	for (auto& it : mShaderObjects) {
		if (it->mFilePath == mRootPath + shaderName) {
			return it->mShader;
		}
	}
	puShaderObject shaderObject = puShaderObject(new ShaderObject());
	shaderObject->mFilePath = mRootPath + shaderName;

	const unsigned int type = shaderType;

	shaderObject->mShader = pShader(new core::Shader(type, shaderSource));
	mShaderObjects.push_back(std::move(shaderObject));
	return mShaderObjects.back()->mShader;
}

pShader ShaderManager::get(std::string path) {
	for (auto& it : mShaderObjects) {
		if (it->mFilePath == (mRootPath + path)) {
			FLOG_DEBUG("Shader %s was found in manager. Returning shader pointer",
					it->mFilePath.c_str());
			return it->mShader;
		}
	}
	FLOG_ERROR("Shader %s not found in manager. Returning empty pointer",
			path.c_str());
	return pShader();
}

void ShaderManager::reload() {
	for (auto& it : mShaderObjects) {
		it->mShader->reload();
	}
	FLOG_DEBUG("Shaders reloaded");
}

} /* manager */
} /* fillwave */
