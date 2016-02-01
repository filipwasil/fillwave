/*
 * ProgramManager.h
 *
 *  Created on: 15 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef PROGRAMMANAGER_H_
#define PROGRAMMANAGER_H_

#include <fillwave/core/pipeline/Program.h>
#include <fillwave/management/base/ManagerNested.h>

namespace fillwave {
namespace framework {

/**
 * Data structure containing each Program instance info.
 */
struct ProgramObject {
	ProgramObject(const std::string& name, const std::vector<pShader>& shaders, GLboolean skipLinking)
			: mName(name),
			  mContent(std::make_shared<core::Program>(shaders, skipLinking)) {

	}

	~ProgramObject() = default;

	std::string mName;
	pProgram mContent;
};

/**
 * Program manager
 */
typedef ManagerNested<std::unique_ptr<ProgramObject>, pProgram, std::string, UINT_MAX, PolicyUnique<ProgramObject>,
		const std::string&, const std::vector<pShader>&, GLboolean> ManagerPrograms;

} /* framework */
} /* fillwave */

#endif /* PROGRAMMANAGER_H_ */
