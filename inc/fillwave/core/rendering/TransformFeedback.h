/*
 * TransformFeedback.h
 *
 *  Created on: May 30, 2014
 *      Author: Filip Wasil
 *
 * Fillwave C++11 graphics Engine
 *
 * Copyright (C) 2016 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This library is available free of charge for any commercial
 * or non-commercial use. However, You are obligated to put a clearly
 * visible information in Your license agreement that Your Software
 * uses Fillwave library to handle graphics management.
 * If You are interested in extra support, extra features
 * or cooperation I look forward to hearing from You.
 *
 * fillwave@gmail.com
 *
 */


#ifndef TRANSFORMFEEDBACK_H_
#define TRANSFORMFEEDBACK_H_

#include <fillwave/core/GLObject.h>
#include <fillwave/common/PtrShared.h>

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
typedef framework::PtrShared<core::TransformFeedback> pTransformFeedback;
} /* fillwave */

#endif /* TRANSFORMFEEDBACK_H_ */
