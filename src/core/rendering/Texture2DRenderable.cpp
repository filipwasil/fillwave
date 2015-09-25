/*
 * Texture2DRenderable.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: Filip Wasil
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * filip.wasil@gmail.com
 *
 */

#include <fillwave/core/rendering/Texture2DRenderable.h>
#include <fillwave/extras/Log.h>

FLOGINIT("Texture2DRenderable", FERROR | FFATAL | FDEBUG)

namespace fillwave {
namespace core {

Texture2DRenderable::Texture2DRenderable(GLenum attachment,
                                         puTexture2DFile file,
                                         ParameterList& parameters)
:Texture2D(std::move(file), parameters),
 mFramebuffer(puFramebuffer (new Framebuffer())),
 mAttachment(attachment) {
   setAttachment(attachment);
}

Texture2DRenderable::~Texture2DRenderable() {
}

void Texture2DRenderable::resize(GLint width, GLint heigth) {
   mFile->mHeader.mWidth = width;
   mFile->mHeader.mHeight = heigth;
   mFile->mData = nullptr;
   bind();
   sendData();
   unbind();
}

void Texture2DRenderable::bindForWriting() {
   mFramebuffer->bindForWriting();
}

void Texture2DRenderable::bindForRendering() {
   mFramebuffer->bind();
}

void Texture2DRenderable::bindForReading() {
   mFramebuffer->bindForReading();
}

void Texture2DRenderable::setAttachment(GLenum attachment, GLenum target) {
   GLenum none = GL_NONE;

   switch(attachment) {
      case GL_DEPTH_STENCIL_ATTACHMENT:
         bind();
         bindForRendering();
         mFramebuffer->attachTexture2D(GL_DEPTH_STENCIL_ATTACHMENT, target, getHandle());
         FLOG_CHECK("Setting depth framebuffer failed");
         Framebuffer::bindScreenFramebuffer();
         break;
      case GL_DEPTH_ATTACHMENT:
         bind();
         bindForRendering();
         mFramebuffer->attachTexture2D(GL_DEPTH_ATTACHMENT, target, getHandle());
         #ifndef __ANDROID__
            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE); //xxx this does not have to be here
         #else
            glDrawBuffers(1,&none);
            glReadBuffer(GL_NONE); //xxx this does not have to be here
         #endif
         FLOG_CHECK("Setting depth framebuffer failed");
         Framebuffer::bindScreenFramebuffer();
         break;
      case GL_COLOR_ATTACHMENT0:
         bind();
         bindForRendering();
         mFramebuffer->attachTexture2D(GL_COLOR_ATTACHMENT0, target, getHandle());
         FLOG_CHECK("Setting RGBA framebuffer failed");
         unbind();
         Framebuffer::bindScreenFramebuffer();
         break;
   }
}

void Texture2DRenderable::attachTexture2DDraw(GLenum attachment, GLenum target, GLuint textureHandle) {
   mFramebuffer->attachTexture2DDraw(attachment, target, textureHandle);
}

void Texture2DRenderable::attachTexture2D(GLenum attachment, GLenum target, GLuint textureHandle) {
   mFramebuffer->attachTexture2D(attachment, target, textureHandle);
}

void Texture2DRenderable::copyTo(Framebuffer* source) {
   source->bindForWriting();
   mFramebuffer->bindForReading(); /* We will bind framebufferuffer for reading ...*/
   mFramebuffer->setReadColorAttachment(0); /* .. and take color attachment color 0 ... */
   glBlitFramebuffer(0,
                0,
                mFile->mHeader.mWidth,
                mFile->mHeader.mHeight,
                0,
                0,
                mFile->mHeader.mWidth,
                mFile->mHeader.mHeight,
                GL_COLOR_BUFFER_BIT,
                GL_LINEAR); /* ... to finally copy it into main framebuffer */
}

void Texture2DRenderable::copyFrom(Framebuffer* source) {
   mFramebuffer->bindForWriting();
   source->bindForReading();
   source->setReadColorAttachment(0);
   glBlitFramebuffer(0,
                0,
                mFile->mHeader.mWidth,
                mFile->mHeader.mHeight,
                0,
                0,
                mFile->mHeader.mWidth,
                mFile->mHeader.mHeight,
                GL_COLOR_BUFFER_BIT,
                GL_LINEAR); /* ... to finally copy it into main framebuffer */
}

void Texture2DRenderable::log() {

}


void Texture2DRenderable::reload() {
   Texture2D::reload();
   mFramebuffer->reload();
   setAttachment(mAttachment);
}

} /* core */
} /* fillwave */
