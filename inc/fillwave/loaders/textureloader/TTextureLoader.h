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
#include <string>

namespace flw {
namespace flf {

/*! \class Textureloader
 * \brief Loads textures
 */
template<class Traits>
struct TTextureLoader {

  flc::TextureConfig* load(
    const std::string& filePath
    , flc::EFlip flip = flc::EFlip::none
    , GLenum format = GL_RGBA
    , std::string rootPath = ""
    , flc::ECompression compression = flc::ECompression::none
    , GLenum cubeTarget = 0);

  flc::TextureConfig* load(
    GLint screenWidth
    , GLint screenHeight
    , GLenum format = GL_RGBA);

  const std::vector<flc::ECompression> getSupportedCompressionFormats();
};

} /* flw */
} /* flf */
