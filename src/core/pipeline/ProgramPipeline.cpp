/*
 * ProgramPipeline.cpp
 *
 *  Created on: May 30, 2014
 *      Author: filip
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

#ifndef __ANDROID__

#include <fillwave/core/pipeline/ProgramPipeline.h>
#include <fillwave/extras/Log.h>

namespace fillwave {
namespace core {

ProgramPipeline::ProgramPipeline(GLbitfield stage,
                                 GLsizei howMany )
:GLObject(howMany),
 mStage(stage),
 mTarget(GL_TRANSFORM_FEEDBACK){
   glGenProgramPipelines(mHowMany, mHandles);
}

ProgramPipeline::~ProgramPipeline() {
   glDeleteProgramPipelines(mHowMany, mHandles);
}

void ProgramPipeline::bind(GLuint id) {
   glBindProgramPipeline(mHandles[id]);
}

void ProgramPipeline::use(GLuint programHandle, GLuint id) {
   glUseProgramStages(mHandles[id], mStage, programHandle);
}

} /* core */
} /* fillwave  */

#endif /* __ANDROID__ */
