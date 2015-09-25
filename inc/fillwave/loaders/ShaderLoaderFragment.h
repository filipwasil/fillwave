/*
 * ShaderLoaderFragment.h
 *
 *  Created on: 13 May 2015
 *      Author: Filip Wasil
 */

#ifndef SHADERLOADERFRAGMENT_H_
#define SHADERLOADERFRAGMENT_H_

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
#include <fillwave/OpenGL.h>

namespace fillwave {
namespace loader {

/*! \class ShaderLoaderFragment
 * \brief ShaderLoader to load fragment shader sources.
 */

class ShaderLoaderFragment: public ShaderLoader {
public:
	ShaderLoaderFragment(
			eShaderLoaderOpenGLVersion version,
			eShaderLoaderPrecision precisionInt,
			eShaderLoaderPrecision precisionFloat,
			GLuint renderTargets = 1);

	virtual ~ShaderLoaderFragment();

	const std::string getSource();

private:
	GLboolean mFog;
	GLboolean mColor;
	GLboolean mColorBoost;
	GLboolean mTextureOnly;
	GLboolean mPointLights;
	GLuint mRendertargets;
};

} /* loader */
} /* fillwave */

#endif /* SHADERLOADERFRAGMENT_H_ */
