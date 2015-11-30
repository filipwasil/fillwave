/*
 * ShaderLoader.h
 *
 *  Created on: 13 May 2015
 *      Author: Filip Wasil
 */

#ifndef SHADERLOADER_H_
#define SHADERLOADER_H_

#include <string>

namespace fillwave {
namespace loader {

enum class eShaderLoaderOpenGLVersion {
	eOpenGL, eOpenGLES
};

enum class eShaderLoaderPrecision {
	eDefaultp, eHighp, eMediump, eLowp
};

/*! \class ShaderLoader
 * \brief Loads shader sources.
 */

class ShaderLoader {
protected:
	eShaderLoaderOpenGLVersion mVersion;
	eShaderLoaderPrecision mPrecisionFloat;
	eShaderLoaderPrecision mPrecisionInt;

#if defined(FILLWAVE_GLES_2_0)
	const std::string mGLVaryingIn = "varying";
	const std::string mGLVaryingOut = "varying";
#else /* defined(FILLWAVE_GLES_2_0) */
	const std::string mGLVaryingIn = "in";
	const std::string mGLVaryingOut = "out";
#endif /* defined(FILLWAVE_GLES_2_0) */

public:
	ShaderLoader(
			eShaderLoaderOpenGLVersion version,
			eShaderLoaderPrecision precisionInt,
			eShaderLoaderPrecision precisionFloat)
			:
					mVersion(version),
					mPrecisionFloat(precisionFloat),
					mPrecisionInt(precisionInt) {

	}
	virtual ~ShaderLoader() = default;
	virtual const std::string getSource() const = 0;
};

} /* loader */
} /* fillwave */

#endif /* SHADERLOADER_H_ */
