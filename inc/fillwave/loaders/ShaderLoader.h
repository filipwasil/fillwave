/*
 * ShaderLoader.h
 *
 *  Created on: 13 May 2015
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SHADERLOADER_H_
#define SHADERLOADER_H_

#include <fillwave/OpenGL.h>
#include <string>

namespace fillwave {
namespace framework {

/*! \class ShaderLoader
 * \brief Loads shader sources.
 */

class ShaderLoader {
 protected:
#if defined(FILLWAVE_GLES_3_0)
	const std::string mGLVersion = "#version 300 es\n";
	const std::string mGLFragmentPrecision = "precision lowp float;\n";
	const std::string mGLVertexPrecision = "precision mediump float;\n";
#else /* defined(FILLWAVE_GLES_3_0) */
	const std::string mGLVersion = "#version 330 core\n";
	const std::string mGLFragmentPrecision = "\n";
	const std::string mGLVertexPrecision = "\n";
#endif /* defined(FILLWAVE_GLES_3_0) */

#if defined(FILLWAVE_GLES_2_0)
	const std::string mGLVaryingIn = "varying";
	const std::string mGLVaryingOut = "varying";

#else /* defined(FILLWAVE_GLES_2_0) */
	const std::string mGLVaryingIn = "in";
	const std::string mGLVaryingOut = "out";

#endif /* defined(FILLWAVE_GLES_2_0) */

 public:
	ShaderLoader() = default;
	virtual ~ShaderLoader() = default;
};

} /* framework */
} /* fillwave */

#endif /* SHADERLOADER_H_ */
