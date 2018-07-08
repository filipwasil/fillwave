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

namespace flw {
namespace flc {

/*! \enum EMemoryAllocation
 * \brief Stores the type of memory free method
 */
enum class EMemoryAllocation {
  cstyle
  , standard
  , none
};

// generic formats

//GL_COMPRESSED_RED,
//GL_COMPRESSED_RG,
//GL_COMPRESSED_RGB,
//GL_COMPRESSED_RGBA.
//GL_COMPRESSED_SRGB,
//GL_COMPRESSED_SRGB_ALPHA.

// extented formats
//GL_COMPRESSED_LUMINANCE_LATC1_EXT
//GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT
//GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT
//GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT

//GL_COMPRESSED_RED_RGTC1_EXT
//GL_COMPRESSED_SIGNED_RED_RGTC1_EXT
//GL_COMPRESSED_RED_GREEN_RGTC2_EXT
//GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT

//GL_COMPRESSED_RGB_S3TC_DXT1_EXT
//GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
//GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
//GL_COMPRESSED_RGBA_S3TC_DXT5_EXT

} /* flw */
} /* flf */
