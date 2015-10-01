/*
 * Query.h
 *
 *  Created on: May 17, 2015
 *      Author: filip
 */

#ifndef INC_FILLWAVE_CORE_QUERY_H_
#define INC_FILLWAVE_CORE_QUERY_H_

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

namespace fillwave {
namespace core {

/*! \class Query
 * \brief GLObject to ask OpenGL questions.
 */

template <GLenum target>
class Query : public GLObject {
private:
   GLenum mTarget = target;

public:
   Query(GLsizei howMany = 1);

   virtual ~Query();

   void begin(GLuint id = 0);

   void end();

   GLuint getID(GLuint id = 0);

   GLuint getResultSync(GLuint id = 0);

   GLuint getResultAsync(GLuint resultIfNotAvailable, GLuint id = 0);
   
   GLboolean getResultAvailable(GLuint id = 0);

   void reload();

   void log();
};

typedef Query<GL_ANY_SAMPLES_PASSED> QueryIfAnySamplesPassed;

typedef Query<GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN> QueryHowManyTransformFeedbackPrimitivesWritten;

#ifdef __ANDROID__
#else

typedef Query<GL_SAMPLES_PASSED> QueryHowManySamplesPassed;
typedef Query<GL_PRIMITIVES_GENERATED> QueryHowManyPrimitivesGeneratedByGeometryShader;
typedef Query<GL_TIME_ELAPSED> QueryTimeElapsed;

#endif

} /* core */
} /* fillwave */


#endif /* INC_FILLWAVE_CORE_QUERY_H_ */
