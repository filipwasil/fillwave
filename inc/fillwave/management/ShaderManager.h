/*
 * ShaderManager.h
 *
 *  Created on: Apr 17, 2014
 *      Author: Filip Wasil
 */

#ifndef SHADERMANAGER_H_
#define SHADERMANAGER_H_

#include <fillwave/core/pipeline/Shader.h>
#include <fillwave/management/base/TManagerSmart.h>

namespace fillwave {
namespace framework {

typedef TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::Shader,
        std::string, GLuint, const std::string&> ManagerShaders;

} /* framework */
} /* fillwave */
#endif /* SHADERMANAGER_H_ */
