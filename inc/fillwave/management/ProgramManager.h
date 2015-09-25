/*
 * ProgramManager.h
 *
 *  Created on: 15 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef PROGRAMMANAGER_H_
#define PROGRAMMANAGER_H_

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
   ProgramManager();

   virtual ~ProgramManager();

   pProgram add(const std::string& name, const std::vector<pShader>& shaders, GLboolean skipLinking) ;

   pProgram get(const std::string& name);

   void reload();

private:
   std::vector<puProgramObject> mProgramObjects;
};

} /* manager */
typedef std::unique_ptr<manager::ProgramManager> puProgramManager;
} /* fillwave */

#endif /* PROGRAMMANAGER_H_ */
