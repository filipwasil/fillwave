/*
 * Texture2DRenderable.h
 *
 *  Created on: Aug 13, 2014
 *      Author: filip
 */

#ifndef TEXTURE2DRENDERABLE_H_
#define TEXTURE2DRENDERABLE_H_

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

#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/core/rendering/Framebuffer.h>

namespace fillwave {
namespace core {

/*! \class Texture2DRenderable
 * \brief One can render to this texture and use the rendered image as a 2D texture.
 */

class Texture2DRenderable: public Texture2D {
public:
   Texture2DRenderable(GLenum attachment,
                       puTexture2DFile file,
                       ParameterList& parameters);

   virtual ~Texture2DRenderable();

   void resize(GLint width, GLint height);

   void bindForWriting();

   void bindForRendering();

   void bindForReading();

   void setAttachment(GLenum attachment, GLenum target = GL_TEXTURE_2D);

   void attachTexture2DDraw(GLenum attachment, GLenum target, GLuint textureHandle);

   void attachTexture2D(GLenum attachment, GLenum target, GLuint textureHandle);

   void copyTo(Framebuffer* source);

   void copyFrom(Framebuffer* source);

   virtual void reload();

   void log();

private:
   puFramebuffer mFramebuffer;

   GLenum mAttachment;
};

} /* core */
typedef std::shared_ptr<core::Texture2DRenderable> pTexture2DRenderable;
typedef std::unique_ptr<core::Texture2DRenderable> puTexture2DRenderable;
} /* fillwave */
#endif /* TEXTURE2DRENDERABLE_H_ */
