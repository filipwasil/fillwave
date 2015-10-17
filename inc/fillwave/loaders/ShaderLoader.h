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
	OpenGL, OpenGLES
};

enum class eShaderLoaderPrecision {
	defaultp, highp, mediump, lowp
};

/*! \class ShaderLoader
 * \brief Loads shader sources.
 */

class ShaderLoader {
protected:
	eShaderLoaderOpenGLVersion mVersion;
	eShaderLoaderPrecision mPrecisionFloat;
	eShaderLoaderPrecision mPrecisionInt;
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
