/*
 * ProgramManager.cpp
 *
 *  Created on: 15 Apr 2014
 *      Author: Filip Wasil
 */

#include <fillwave/management/ProgramManager.h>
#include <fillwave/extras/Log.h>
#include <fillwave/core/pipeline/Program.h>

FLOGINIT("ProgramManager", FERROR | FFATAL)

namespace fillwave {
namespace manager {

pProgram ProgramManager::add(
		const std::string& name,
		const std::vector<pShader>& shaders,
		GLboolean skipLinking) {
	for (auto& it : mProgramObjects) {
		if (it->mName == name) {
			return it->mProgram;
		}
	}
	ProgramObject* ptr = new ProgramObject();
	ptr->mProgram = pProgram(new core::Program(shaders, skipLinking));
	ptr->mName = name;
	mProgramObjects.push_back(puProgramObject(ptr));
	return mProgramObjects.back()->mProgram;
}

pProgram ProgramManager::get(const std::string& name) {
	for (auto& it : mProgramObjects) {
		if (it->mName == name) {
			return it->mProgram;
		}
	}
	FLOG_DEBUG("Program %s not found in manager. Returning empty pointer",
			name.c_str());
	return pProgram();
}

void ProgramManager::reload() {
	for (auto& it : mProgramObjects) {
		it->mProgram->reload();
	}
}

} /* manager */
} /* fillwave */
