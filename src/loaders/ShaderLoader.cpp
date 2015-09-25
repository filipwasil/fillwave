/*
 * ShaderLoader.cpp
 *
 *  Created on: 13 May 2015
 *      Author: Filip Wasil
 */

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2015] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/loaders/ShaderLoader.h>

namespace fillwave {
namespace loader {

ShaderLoader::ShaderLoader(eShaderLoaderOpenGLVersion version,
	                       eShaderLoaderPrecision precisionInt,
	                       eShaderLoaderPrecision precisionFloat)
:mVersion(version),
 mPrecisionFloat(precisionFloat),
 mPrecisionInt(precisionInt) {

}

ShaderLoader::~ShaderLoader() {

}

} /* loader */
} /* crater */
