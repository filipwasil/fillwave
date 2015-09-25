/*
 * ShaderManager.h
 *
 *  Created on: Apr 17, 2014
 *      Author: Filip Wasil
 */

#ifndef SHADERMANAGER_H_
#define SHADERMANAGER_H_

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

#include <fillwave/extras/Log.h>
#include <fillwave/loaders/FileLoader.h>
#include <fillwave/core/pipeline/Shader.h>

namespace fillwave {
class Engine;
namespace manager {

/*! \struct ShaderObject
 *
 * \brief Data structure containing each Shader instance info.
 *
 */

struct ShaderObject {
	std::string mFilePath;
	pShader mShader;

	void reload(Engine* engine);
};

typedef std::unique_ptr<ShaderObject> puShaderObject;

/*! \class ShaderManager
 *
 * \brief Manager to handle ShaderObject objects.
 *
 */

class ShaderManager {
private:
	std::string mRootPath;
public:
	ShaderManager(const std::string& rootPath);
	virtual ~ShaderManager();

	pShader add(const std::string& shaderPath, const unsigned int shaderType);
	pShader add(
			const std::string& shaderName,
			const int shaderType,
			const std::string& shaderSource);
	pShader get(std::string path);

	std::vector<puShaderObject> mShaderObjects;

	void reload();
};

} /* manager */
typedef std::unique_ptr<manager::ShaderManager> puShaderManager;
} /* fillwave */
#endif /* SHADERMANAGER_H_ */
