/*
 * TransformFeedback.h
 *
 *  Created on: May 30, 2014
 *      Author: Filip Wasil
 */

#ifndef TRANSFORMFEEDBACK_H_
#define TRANSFORMFEEDBACK_H_

#include <fillwave/core/GLObject.h>

#include <memory>

namespace fillwave {
namespace core {

/*! \class TransformFeedback
 * \brief Used for GPU side comutations.
 */

class TransformFeedback: public GLObject {
public:
	TransformFeedback(GLsizei howMany = 1);

	virtual ~TransformFeedback();

	void bind(GLuint id = 0) const;

	static void begin(GLenum primitiveMode);

	static void end();

	static void pause();

	static void resume();

private:
	GLuint mTarget;
};

} /* core */
typedef std::shared_ptr<core::TransformFeedback> pTransformFeedback;
} /* fillwave */

#endif /* TRANSFORMFEEDBACK_H_ */
