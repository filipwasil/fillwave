/*
 * VertexArray.h
 *
 *  Created on: 4 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef VERTEX_ARRAY_H_
#define VERTEX_ARRAY_H_

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

/*! \class VertexArray
 * \brief VertexArrayObject - VAO
 */

class VertexArray : public GLObject {
public:
   VertexArray(GLuint howMany = 1);

   virtual ~VertexArray();

   void bind(GLuint id = 0);

   void unbind();

   void reload();
};

} /* buffer */
typedef std::shared_ptr<core::VertexArray> pVertexArray;
typedef std::weak_ptr<core::VertexArray> pwVertexArray;
} /* fillwave */

#endif /* ARRAY_H_ */
