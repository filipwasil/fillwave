/*
 * ConditionalRender.h
 *
 *  Created on: May 17, 2015
 *      Author: filip
 */

#ifndef INC_FILLWAVE_OPERATIONS_CONDITIONALRENDER_H_
#define INC_FILLWAVE_OPERATIONS_CONDITIONALRENDER_H_

#ifdef __ANDROID__
#else

#include <fillwave/OpenGL.h>

namespace fillwave {
namespace core {

/*! \class ConditionalRender
 * \brief Operation of rendering only meshes passing the occlusion test.
 */

class ConditionalRender {
public:

	/*!
	 * \brief Specifies the conditional rendering pass mode.
	 *
	 * \param Possible modes:
	 *  GL_QUERY_WAIT,
	 *  GL_QUERY_NO_WAIT,
	 *  GL_QUERY_BY_REGION_WAIT,
	 *  GL_QUERY_BY_REGION_NO_WAIT,
	 */

	ConditionalRender(GLenum mode);

	virtual ~ConditionalRender() = default;

	void begin(GLuint querryID) const;

	void end() const;

private:
	GLenum mMode;
};

} /* core */
} /* fillwave */

#endif

#endif /* INC_FILLWAVE_OPERATIONS_CONDITIONALRENDER_H_ */
