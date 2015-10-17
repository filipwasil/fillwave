/*
 * ProgramManager.h
 *
 *  Created on: 15 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef PROGRAMMANAGER_H_
#define PROGRAMMANAGER_H_

#include <fillwave/core/pipeline/Program.h>

namespace fillwave {
namespace manager {

/*! \struct ProgramObject
 * \brief Data structure containing each Program instance info.
 */

struct ProgramObject {
	std::string mName;
	pProgram mProgram;
};

typedef std::unique_ptr<ProgramObject> puProgramObject;

/*! \class ProgramManager
 * \brief Manager to handle ProgramObjects objects.
 */

class ProgramManager {
public:
	ProgramManager() = default;

	virtual ~ProgramManager() = default;

	pProgram add(
			const std::string& name,
			const std::vector<pShader>& shaders,
			GLboolean skipLinking);

	pProgram get(const std::string& name);

	void reload();

private:
	std::vector<puProgramObject> mProgramObjects;
};

} /* manager */
typedef std::unique_ptr<manager::ProgramManager> puProgramManager;
} /* fillwave */

#endif /* PROGRAMMANAGER_H_ */
