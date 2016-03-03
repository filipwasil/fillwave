/*
 * ProgramManager.h
 *
 *  Created on: 15 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef PROGRAMMANAGER_H_
#define PROGRAMMANAGER_H_

#include <fillwave/core/pipeline/Program.h>
#include <fillwave/management/base/TManagerComposite.h>

namespace fillwave {
namespace framework {

/**
 * Data structure containing each Sampler instance info.
 */
typedef Composition<pProgram, TPolicyShared<core::Program>,
		const std::vector<pShader>&, GLboolean> ProgramObject;

/**
 * Program manager
 */
typedef ManagerComposite<std::unique_ptr<ProgramObject>, pProgram, std::string,
		UINT_MAX, TPolicyUnique<ProgramObject>, const std::vector<pShader>&,
		GLboolean> ManagerPrograms;

} /* framework */
} /* fillwave */

#endif /* PROGRAMMANAGER_H_ */
