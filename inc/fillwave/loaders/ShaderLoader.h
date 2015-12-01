/*
 * ShaderLoader.h
 *
 *  Created on: 13 May 2015
 *      Author: Filip Wasil
 */

#ifndef SHADERLOADER_H_
#define SHADERLOADER_H_

#include <fillwave/OpenGL.h>
#include <string>

namespace fillwave {
namespace loader {

/*! \class ShaderLoader
 * \brief Loads shader sources.
 */

class ShaderLoader {
protected:
#if defined(FILLWAVE_GLES_3_0)
	const std::string mGLVersion = "#version 300 es\n";
	const std::string mGLFragmentPrecision = "precision lowp float;\n";
	const std::string mGLVertexPrecision = "precision mediump float;\n";
#elif defined(FILLWAVE_GLES_2_0)
	const std::string mGLVersion = "#version 200 es\n";
	const std::string mGLFragmentPrecision = "precision lowp float;\n";
	const std::string mGLVertexPrecision = "precision mediump float;\n";
#else /* defined(FILLWAVE_GLES_3_0) || defined(FILLWAVE_GLES_2_0) */
	const std::string mGLVersion = "#version 330 core\n";
	const std::string mGLFragmentPrecision = "\n";
	const std::string mGLVertexPrecision = "\n";
#endif /* defined(FILLWAVE_GLES_3_0) || defined(FILLWAVE_GLES_2_0) */

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

} /* loader */
} /* fillwave */

#endif /* SHADERLOADER_H_ */
