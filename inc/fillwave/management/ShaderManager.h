/*
 * ShaderManager.h
 *
 *  Created on: Apr 17, 2014
 *      Author: Filip Wasil
 */

#ifndef SHADERMANAGER_H_
#define SHADERMANAGER_H_

#include <fillwave/extras/Log.h>
#include <fillwave/loaders/FileLoader.h>
#include <fillwave/core/pipeline/Shader.h>

namespace fillwave {
class Engine;
namespace manager {

/*! \struct ShaderObject
 * \brief Data structure containing each Shader instance info.
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
	virtual ~ShaderManager() = default;

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
