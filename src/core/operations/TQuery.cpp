/*
 * Query.cpp
 *
 *  Created on: May 17, 2015
 *      Author: filip
 */

#include <fillwave/core/operations/TQuery.h>
#include <fillwave/Log.h>

FLOGINIT("Query", FERROR | FFATAL | FINFO)

namespace fillwave {
namespace core {

template <GLenum target>
TQuery<target>::TQuery(GLsizei howMany) :
	GLObject(howMany) {
	glGenQueries(mHowMany, mHandles);
	FLOG_CHECK("Could not create query");
}

template <GLenum target>
TQuery<target>::~TQuery() {
	glDeleteQueries(mHowMany, mHandles);
	FLOG_CHECK("Could not delete query");
}

template <GLenum target>
GLuint TQuery<target>::getID(GLuint id) const {
	return mHandles[id];
}

template <GLenum target>
void TQuery<target>::begin(GLuint id) {
	glBeginQuery(mTarget, mHandles[id]);
	FLOG_CHECK("Could not begin query");
}

template <GLenum target>
void TQuery<target>::end() {
	glEndQuery(mTarget);
	FLOG_CHECK("Could not end query");
}

template <GLenum target>
GLuint TQuery<target>::getResultAsync(GLuint resultIfNotAvailable, GLuint id) {
	GLuint result;
	glGetQueryObjectuiv(mHandles[id], GL_QUERY_RESULT_AVAILABLE, &result);
	FLOG_CHECK("Could not get querry result state");
	if (result) {
		glGetQueryObjectuiv(mHandles[id], GL_QUERY_RESULT, &result);
		FLOG_CHECK("Could not get query async result");
		return result;
	} else {
		return resultIfNotAvailable;
	}
}

template <GLenum target>
GLuint TQuery<target>::getResultSync(GLuint id) {
	GLuint result;
	glGetQueryObjectuiv(mHandles[id], GL_QUERY_RESULT, &result);
	FLOG_CHECK("Could not get querry sync result");
	return result;
}

template <GLenum target>
GLboolean TQuery<target>::getResultAvailable(GLuint id) {
	GLuint result;
	glGetQueryObjectuiv(mHandles[id], GL_QUERY_RESULT_AVAILABLE, &result);
	return result ? GL_TRUE : GL_FALSE;
}

template <GLenum target>
void TQuery<target>::reload() {
	glGenQueries(mHowMany, mHandles);
	FLOG_CHECK("reload");
}

template <GLenum target>
void TQuery<target>::log() {
	for (GLsizei id = 0; id < mHowMany; id++) {
		if (glIsQuery(mHandles[id])) {
			FLOG_INFO("Query %d exists", mHandles[id]);
		} else {
			FLOG_INFO("Query %d does not exist", mHandles[id]);
		}
	}
}

template class TQuery<GL_ANY_SAMPLES_PASSED> ;
template class TQuery<GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN> ;

#ifdef FILLWAVE_GLES_3_0
#else
template class TQuery<GL_SAMPLES_PASSED> ;
template class TQuery<GL_PRIMITIVES_GENERATED> ;
template class TQuery<GL_TIME_ELAPSED> ;
#endif

} /* core */
} /* fillwave */
