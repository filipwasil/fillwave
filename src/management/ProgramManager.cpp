/*
 * ProgramManager.cpp
 *
 *  Created on: 15 Apr 2014
 *      Author: Filip Wasil
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

#include <fillwave/management/ProgramManager.h>
#include <fillwave/extras/Log.h>
#include <fillwave/core/pipeline/Program.h>

FLOGINIT("ProgramManager", FERROR | FFATAL)

namespace fillwave {
namespace manager {

ProgramManager::ProgramManager() {

}

ProgramManager::~ProgramManager() {

}

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
