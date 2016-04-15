/*
 * Buffer.h
 *
 * Created on: 1 Mar 2013
 * Author: Filip Wasil
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <fillwave/core/GLObject.h>
#include <fillwave/Log.h>
#include <memory>

namespace fillwave {
namespace core {

/*! \class Buffer
 * \brief Base for all buffer types.
 */

class IBuffer: public GLObject {
 public:
	IBuffer(
	   GLuint target,
	   GLuint drawType = GL_STATIC_DRAW,
	   GLuint index = 0,
	   GLsizei howMany = 1);

	virtual ~IBuffer();

	void bind(GLuint id = 0) const;
	void bind(GLuint externalTarget, GLuint id) const;
	void bindBase(GLuint id = 0) const;
	void bindBase(GLuint externalTarget, GLuint id) const;
	void unbind();
	void unbindBase(GLuint externalTarget);

	void unmap() const;
	void send();

	void setTarget(GLuint target);
	void setDrawType(GLuint drawType);

	bool isLoaded();
	void setLoaded(GLboolean loaded);

	GLuint getElements() const;
	GLuint getSize() const;
	GLvoid* getData() const;

	void reload();

	GLvoid* mapRange(GLenum access, GLuint size = 0);

	/* Feature not available in OpenGL ES  < 3.1 */
#ifdef FILLWAVE_GLES_3_0
#else
	GLvoid* map(GLenum access) const;
#endif

 protected:
	GLboolean mLoaded;
	GLuint mTarget;
	GLuint mDataStoreType;
	GLuint mIndex;
	GLvoid* mData;
	GLuint mSize;
	GLuint mTotalElements;
	void setElements(GLuint elements);
	void setSize(GLuint size);
	virtual void emptyCPU() = 0;
	virtual void emptyGPU() = 0;
};

void unbindBuffer(GLuint target);
void bindBuffer(GLuint target, GLuint handle);

} /* core */
} /* fillwave */

#endif /* BUFFER_H_ */
