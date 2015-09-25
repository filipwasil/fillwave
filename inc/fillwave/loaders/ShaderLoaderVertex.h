/*
 * ShaderLoaderVertex.h
 *
 *  Created on: 13 May 2015
 *      Author: Filip Wasil
 */

#ifndef SHADERLOADERVERTEX_H_
#define SHADERLOADERVERTEX_H_

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

#include <fillwave/loaders/ShaderLoader.h>

namespace fillwave {
namespace loader {

/*! \class ShaderLoaderVertex
 * \brief ShaderLoader to load vertex shader sources.
 */

class ShaderLoaderVertex: public ShaderLoader {
public:
	ShaderLoaderVertex(eShaderLoaderOpenGLVersion version,
		               eShaderLoaderPrecision precisionInt,
		               eShaderLoaderPrecision precisionFloat,
		               bool animated = false);

	virtual ~ShaderLoaderVertex();

	const std::string getSource();

private:
   bool mAnimated;
};

} /* loader */
} /* fillwave */

#endif /* SHADERLOADERVERTEX_H_ */
