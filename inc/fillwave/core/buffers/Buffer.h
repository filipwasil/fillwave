/*
 * Buffer.h
 *
 * Created on: 1 Mar 2013
 * Author: Filip Wasil
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <fillwave/core/GLObject.h>
#include <fillwave/extras/Log.h>
#include <memory>

namespace fillwave {
namespace core {

/*! \class Buffer
 * \brief Base for all buffer types.
 */

class Buffer: public GLObject {
public:
	Buffer(
			GLuint target,
			GLuint drawType = GL_STATIC_DRAW,
			GLuint index = 0,
			GLsizei howMany = 1);

	virtual ~Buffer();

	void bind(GLuint id = 0) const;

	void bind(GLuint externalTarget, GLuint id) const;

	void bindBase(GLuint id = 0) const;

	void bindBase(GLuint externalTarget, GLuint id) const;

	void unbind();

	void unbindBase(GLuint externalTarget);

	GLvoid* mapRange(GLenum access, GLuint size = 0);

	void unmap() const;

	void send();

	void setTarget(GLuint target);

	void setDrawType(GLuint drawType);

	bool isReady();

	void setReady();

	void resetReady();

	GLuint getElements() const;

	GLuint getSize() const;

	GLvoid* getData() const;

	void reload();

	/* Feature not available in OpenGL ES  <= 3.0 */
#ifndef __ANDROID__
	GLvoid* map(GLenum access) const;
#endif

protected:
	GLboolean mRefresh;
	GLuint mTarget;
	GLuint mDataStoreType;
	GLuint mIndex;
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
