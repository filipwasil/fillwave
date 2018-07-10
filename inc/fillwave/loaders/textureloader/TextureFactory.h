#pragma once

/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sll copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <fillwave/loaders/textureloader/TextureConfigs.h>
#include <fillwave/loaders/textureloader/TextureContent.h>

namespace flw {
namespace flf {

/*! \class TextureGenerator
 * \brief Generates textures
 */
struct TextureFactory {
  static flc::TextureConfig* loadEmpty(
    GLint screenWidth
    , GLint screenHeight
    , GLenum format = GL_RGBA);

  static flc::TextureConfig* loadVirtualFileCheckboard(
    GLuint width
    , GLuint height
    , GLubyte red
    , GLubyte green
    , GLubyte blue
    , GLenum format = GL_RGBA);

  static flc::TextureConfig* loadVirtualFileColor(
    GLuint width
    , GLuint height
    , GLubyte red
    , GLubyte green
    , GLubyte blue
    , GLenum format = GL_RGBA);
};

} /* flw */
} /* flf */
