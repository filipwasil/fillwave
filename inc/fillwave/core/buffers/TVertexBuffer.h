/*
 * VertexBuffer.h
 *
 *  Created on: Jul 20, 2014
 *      Author: filip
 */

#ifndef VERTEXBUFFER_H_
#define VERTEXBUFFER_H_

#include <fillwave/core/buffers/Buffer.h>
#include <fillwave/core/pipeline/Attribute.h>
#include <fillwave/models/shapes/Shape.h>

#include <algorithm>

namespace fillwave {
namespace core {

class Attribute;

/*! \class TVertexBuffer
 * \brief Template for all vertex buffers.
 */

template <class T>
class TVertexBuffer: public Buffer {
 public:
	/* Notice
	 * In this constructor one should initialize:
	 *  - mDataVertices -> vector of <T> data
	 *
	 *  mData = mDataVertices.data();
	 *  mTotalElements = mDataVertices.size();
	 *  mSize = mTotalElements*sizeof(<T>);
	 */

	TVertexBuffer(GLuint dataStoreModification = GL_STATIC_DRAW) :
		Buffer(GL_ARRAY_BUFFER, dataStoreModification) {
	}

	TVertexBuffer(std::vector<T>& vertices, GLuint dataStoreModification =
	                 GL_STATIC_DRAW) :
		Buffer(GL_ARRAY_BUFFER, dataStoreModification) {
		mDataVertices = vertices;
		mTotalElements = mDataVertices.size();
		mData = mDataVertices.data();
		mSize = mTotalElements * sizeof(T);
	}

	TVertexBuffer(framework::Shape<T>& shape, GLuint dataStoreModification =
	                 GL_STATIC_DRAW) :
		Buffer(GL_ARRAY_BUFFER, dataStoreModification) {
		mDataVertices = shape.getVertices();
		mSize = mTotalElements * sizeof(T);
		mData = mDataVertices.data();
	}

	~TVertexBuffer() = default;

	void load(T element) {
		mDataVertices.push_back(element);
		mTotalElements++;
		mSize = mTotalElements * sizeof(T);
		mData = mDataVertices.data();
	}

	void getAttributes(GLint programHandle) {
		int howMany = -1;
		glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTES, &howMany);
		for (int i = 0; i < howMany; ++i) {
			int name_len = -1, num = -1;
			GLenum type = GL_ZERO;
			char name[200];
			glGetActiveAttrib(programHandle, GLuint(i), sizeof(name) - 1,
			                  &name_len, &num, &type, name);
			name[name_len] = 0;
			GLuint location = glGetAttribLocation(programHandle, name);
			GLuint size = 0;
			switch (type) {
				case GL_UNSIGNED_INT:
				case GL_FLOAT:
				case GL_INT:
				case GL_BOOL:
					size = 1;
					break;
				case GL_FLOAT_VEC2:
				case GL_INT_VEC2:
				case GL_BOOL_VEC2:
					size = 2;
					break;
				case GL_FLOAT_VEC3:
				case GL_INT_VEC3:
				case GL_BOOL_VEC3:
					size = 3;
					break;
				case GL_FLOAT_VEC4:
				case GL_INT_VEC4:
				case GL_BOOL_VEC4:
				case GL_FLOAT_MAT2:
					size = 4;
					break;
				case GL_FLOAT_MAT3:
					size = 9;
					break;
				case GL_FLOAT_MAT4:
					size = 16;
					break;
//#ifdef FILLWAVE_GLES_3_0
//#else
				case GL_UNSIGNED_INT_VEC3:
					size = 3;
					break;
				case GL_UNSIGNED_INT_VEC2:
					size = 2;
					break;
				case GL_UNSIGNED_INT_VEC4:
					size = 4;
					break;
//#endif
				default:
					std::cout << "Not supported type of attribute" << std::endl;
					size = 0;
					break;
			}
			Attribute a(name, location, size, sizeof(T), type);
			mAttributes.push_back(a);
		}

		unsigned long long pointer = 0;
		for (GLuint i = 0; i < mAttributes.size(); i++) {
			for (auto& it : mAttributes) {
				if (it.getIndex() == i) {
					it.setOffsetPointer((GLvoid*) pointer);
					pointer += it.getSize() * it.getTypeSize();
				}
			}
		}
	}

	void attributesBind(core::Program* program) {
		GLuint programHandle = program->getHandle();
		std::for_each(mAttributes.begin(), mAttributes.end(),
		[programHandle](Attribute & a) {
			a.bindLocation(programHandle);
		});
	}

	void attributesSetForVAO() {
		std::for_each(mAttributes.begin(), mAttributes.end(),
		[](Attribute & a) {
			a.arrayEnable();
		});
		std::for_each(mAttributes.begin(), mAttributes.end(),
		[](Attribute & a) {
			a.arraySet();
		});
	}

	void attributesEnable() {
		std::for_each(mAttributes.begin(), mAttributes.end(),
		[](Attribute & a) {
			a.arrayEnable();
		});
	}

	void reload() {
		Buffer::reload();
	}

	void attributesSetPointer() {
		std::for_each(mAttributes.begin(), mAttributes.end(),
		[](Attribute & a) {
			a.arraySet();
		});
	}

	T* getDataInternal() {
		return mDataVertices.data();
	}

	virtual void log() const = 0;

 protected:
	std::vector<T> mDataVertices;

 private:
	std::vector<Attribute> mAttributes;
};

} /* core */
} /* fillwave */

#endif /* VERTEXBUFFER_H_ */
