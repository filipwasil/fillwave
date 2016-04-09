/*
 * ProgramManager.h
 *
 *  Created on: 15 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef PROGRAMMANAGER_H_
#define PROGRAMMANAGER_H_

#include <fillwave/core/pipeline/Program.h>
#include <fillwave/management/base/TManagerSmart.h>

namespace fillwave {
namespace framework {

typedef TManagerSmart<FILLWAVE_MANAGEMENT_MAX_ITEMS, core::Program,
        std::string, const std::vector<core::Shader*>&,
        GLboolean> ManagerPrograms;

} /* framework */
} /* fillwave */

#endif /* PROGRAMMANAGER_H_ */
