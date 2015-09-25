/*
 * Attribute.h
 *
 *  Created on: 2 March 2014
 *      Author: Filip Wasil
 */

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

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

#include <fillwave/core/pipeline/Program.h>

namespace fillwave {
namespace core {

/*! \class Attribute
 * \brief VertexAttribute to be kept within the VertexBuffer.
 */

class Attribute {
public:
    Attribute(std::string name,
            GLuint index,
            GLint size,
            GLsizei stride,
            GLenum type,
            GLboolean normalized = GL_FALSE);
    virtual ~Attribute();
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
    std::string mName;
    GLuint mIndex;
    GLint mSize;
    GLenum mType;
    std::size_t mTypeSize;
    GLboolean mNormalized;
    GLsizei mStride;
    GLvoid* mPointer;
};

} /* core */
} /* fillwave */

#endif /* ATTRIBUTE_H_ */
