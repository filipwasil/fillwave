/*
 * ShaderLoader.h
 *
 *  Created on: 13 May 2015
 *      Author: Filip Wasil
 */

#ifndef SHADERLOADER_H_
#define SHADERLOADER_H_

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

#include <string>

namespace fillwave {
namespace loader {

enum class eShaderLoaderOpenGLVersion {
   OpenGL,
   OpenGLES
};

enum class eShaderLoaderPrecision {
   defaultp,
   highp,
   mediump,
   lowp
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
   ShaderLoader(eShaderLoaderOpenGLVersion version,
      eShaderLoaderPrecision precisionInt,
      eShaderLoaderPrecision precisionFloat);
   virtual ~ShaderLoader();
   virtual const std::string getSource() = 0;
};

} /* loader */
} /* fillwave */

#endif /* SHADERLOADER_H_ */
