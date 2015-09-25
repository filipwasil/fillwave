/*
 * Sampler.h
 *
 *  Created on: Mar 30, 2014
 *      Author: Filip Wasil
 */

#ifndef SAMPLER_H_
#define SAMPLER_H_

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
#include <fillwave/core/texturing/Parameter.h>
#include <memory>

namespace fillwave {
namespace core {

/*! \class Sampler
 * \brief SamplerObject - SO.
 */

class Sampler : public GLObject{
public:
   Sampler(GLint textureUnit, GLuint howMany = 1);

   virtual ~Sampler();

//xxx   void bind(GLuint textureUnit, GLuint id = 0);

   void bind(GLuint id = 0);

   void unbind(GLuint id = 0);

   void setParameters(ParameterList parameters);

   void setParameter(GLenum parameter, GLenum value, GLuint id = 0);

   void setParameter(Parameter parameter, GLuint id = 0);

   void reload();

   GLint getTextureUnit();

private:
   GLint mTextureUnit;
};

} /* core */
typedef std::shared_ptr<core::Sampler> pSampler;
typedef std::unique_ptr<core::Sampler> puSampler;
} /* fillwave */

#endif /* SAMPLER_H_ */
