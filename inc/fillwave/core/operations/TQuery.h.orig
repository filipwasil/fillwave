/*
 * Query.h
 *
 *  Created on: May 17, 2015
 *      Author: filip
 */

#ifndef INC_FILLWAVE_CORE_QUERY_H_
#define INC_FILLWAVE_CORE_QUERY_H_

#include <fillwave/core/GLObject.h>

namespace fillwave {
namespace core {

/*! \class TQuery
 * \brief GLObject to ask OpenGL questions.
 */

template <GLenum target>
class TQuery: public GLObject {
private:
	GLenum mTarget = target;

public:
	TQuery(GLsizei howMany = 1);

	virtual ~TQuery();

	void begin(GLuint id = 0);

	void end();

	GLuint getID(GLuint id = 0) const;

	GLuint getResultSync(GLuint id = 0);

	GLuint getResultAsync(GLuint resultIfNotAvailable, GLuint id = 0);

	GLboolean getResultAvailable(GLuint id = 0);

	void reload();

	void log();
};

typedef TQuery<GL_ANY_SAMPLES_PASSED> QueryIfAnySamplesPassed;

typedef TQuery<GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN> QueryHowManyTransformFeedbackPrimitivesWritten;

#ifdef FILLWAVE_GLES_3_0
#else

typedef TQuery<GL_SAMPLES_PASSED> QueryHowManySamplesPassed;
typedef TQuery<GL_PRIMITIVES_GENERATED> QueryHowManyPrimitivesGeneratedByGeometryShader;
typedef TQuery<GL_TIME_ELAPSED> QueryTimeElapsed;

#endif

} /* core */
} /* fillwave */

#endif /* INC_FILLWAVE_CORE_QUERY_H_ */
