/*
 * ProgramPipeline.h
 *
 *  Created on: May 30, 2014
 *      Author: Filip Wasil
 */

#ifndef PROGRAMPIPELINE_H_
#define PROGRAMPIPELINE_H_

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

#include <fillwave/core/GLObject.h>

#ifdef __ANDROID__
#else

namespace fillwave {
namespace core {

/*! \class ProgramPipeline
 * \brief Not used.
 *
 */

class ProgramPipeline : public GLObject {
public:
   ProgramPipeline(GLbitfield stage,
                   GLsizei howMany = 1);
   virtual ~ProgramPipeline();
   void bind(GLuint id = 0);
   void use(GLuint programHandle, GLuint id = 0);

private:
   GLuint  mTarget;
   GLbitfield mStage;
};

} /* core */
} /* fillwave */

#endif /* PROGRAMPIPELINE_H_ */

#endif /* __ANDROID__ */
