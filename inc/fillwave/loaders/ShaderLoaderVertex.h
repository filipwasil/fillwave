/*
 * ShaderLoaderVertex.h
 *
 *  Created on: 13 May 2015
 *      Author: Filip Wasil
 */

#ifndef SHADERLOADERVERTEX_H_
#define SHADERLOADERVERTEX_H_

#include <fillwave/loaders/ShaderLoader.h>

namespace fillwave {
namespace loader {

/*! \class ShaderLoaderVertex
 * \brief ShaderLoader to load vertex shader sources.
 */

class ShaderLoaderVertex: public ShaderLoader {
public:
	ShaderLoaderVertex(
			eShaderLoaderOpenGLVersion version,
			eShaderLoaderPrecision precisionInt,
			eShaderLoaderPrecision precisionFloat,
			bool animated = false);

	virtual ~ShaderLoaderVertex() = default;

	const std::string getSource() const;

private:
	bool mAnimated;
};

} /* loader */
} /* fillwave */

#endif /* SHADERLOADERVERTEX_H_ */
