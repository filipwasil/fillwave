/*
 * Buffer.h
 *
 * Created on: 1 Mar 2013
 * Author: Filip Wasil
 */

#ifndef BUFFER_H_
#define BUFFER_H_

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
#include <fillwave/extras/Log.h>
#include <memory>

namespace fillwave {
namespace core {

/*! \class Buffer
 * \brief Base for all buffer types.
 *
 */

class Buffer: public GLObject {
public:
	Buffer(
			GLuint target,
			GLuint drawType = GL_STATIC_DRAW,
			GLuint index = 0,
			GLsizei howMany = 1);

	virtual ~Buffer();

	void bind(GLuint id = 0);

	void bind(GLuint externalTarget, GLuint id);

	void bindBase(GLuint id = 0);

	void bindBase(GLuint externalTarget, GLuint id);

	void unbind();

	void unbindBase(GLuint externalTarget);

	GLvoid* mapRange(GLenum access, GLuint size = 0);

	void unmap();

	void send();

	void setTarget(GLuint target);

	void setDrawType(GLuint drawType);

	bool isReady();

	void setReady();

	void resetReady();

	GLuint getElements();

	GLuint getSize();

	GLvoid* getData();

	void reload();

	/* Feature not available in OpenGL ES  <= 3.0 */
#ifndef __ANDROID__
	GLvoid* map(GLenum access);
#endif

protected:
	GLuint mIndex;
	GLuint mTarget;
	GLuint mDataStoreType;
	GLboolean mRefresh;
	GLvoid* mData;
	GLuint mSize;
	GLuint mTotalElements;
	void setElements(GLuint elements);
	void setSize(GLuint size);
};

} /* core */
typedef std::shared_ptr<core::Buffer> pBuffer;
typedef std::unique_ptr<core::Buffer> puBuffer;
} /* fillwave */

#endif /* BUFFER_H_ */
