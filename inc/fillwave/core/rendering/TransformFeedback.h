/*
 * TransformFeedback.h
 *
 *  Created on: May 30, 2014
 *      Author: Filip Wasil
 */

#ifndef TRANSFORMFEEDBACK_H_
#define TRANSFORMFEEDBACK_H_

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

	void bind(GLuint id = 0);

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
