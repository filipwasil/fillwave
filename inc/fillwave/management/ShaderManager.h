/*
 * ShaderManager.h
 *
 *  Created on: Apr 17, 2014
 *      Author: Filip Wasil
 */

#ifndef SHADERMANAGER_H_
#define SHADERMANAGER_H_

#include <fillwave/core/pipeline/Shader.h>
#include <fillwave/management/base/TManagerComposite.h>

namespace fillwave {
namespace framework {

/**
 * Data structure containing each Shader instance info.
 */
typedef Composition<pShader, TPolicyShared<core::Shader>, GLuint, const std::string&> ShaderObject;

/**
 * Shader manager
 */
typedef ManagerComposite<std::unique_ptr<ShaderObject>, pShader, std::string,
		UINT_MAX, TPolicyUnique<ShaderObject>, GLuint, const std::string&> ManagerShaders;

} /* framework */
} /* fillwave */
#endif /* SHADERMANAGER_H_ */
