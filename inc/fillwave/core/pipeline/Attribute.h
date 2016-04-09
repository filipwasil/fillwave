/*
 * Attribute.h
 *
 *  Created on: 2 March 2014
 *      Author: Filip Wasil
 */

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include <fillwave/core/pipeline/Program.h>

namespace fillwave {
namespace core {

/*! \class Attribute
 * \brief VertexAttribute to be kept within the VertexBuffer.
 */

class Attribute {
 public:
	Attribute(
	   std::string name,
	   GLuint index,
	   GLint size,
	   GLsizei stride,
	   GLenum type,
	   GLboolean normalized = GL_FALSE);
	virtual ~Attribute() = default;
	void bindLocation(GLint programHandle);
	void arrayDisable();
	void arrayEnable();
	void arraySet();
	void setOffsetPointer(GLvoid* offset);
	GLuint getSize();
	std::size_t getTypeSize();
	GLuint getIndex();
	std::string getName();
	void log();

 private:
	GLsizei mStride;
	std::string mName;
	GLuint mIndex;
	GLint mSize;
	GLboolean mNormalized;
	std::size_t mTypeSize;
	GLenum mType;
	GLvoid* mPointer;
};

} /* core */
} /* fillwave */

#endif /* ATTRIBUTE_H_ */
