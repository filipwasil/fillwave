/*
 * BuilderModelExternalMaps.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: filip
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

#include <fillwave/models/BuilderModelExternalMaps.h>

FLOGINIT("BuilderModelExternalMaps", FERROR | FFATAL)

namespace fillwave {
namespace models {

BuilderModelExternalMaps::BuilderModelExternalMaps(
		Engine* engine,
		std::string modelPath,
		pProgram program,
		std::string diffusePath,
		std::string normalPath,
		std::string specularPath)
		:
				BuilderModel(engine, modelPath, program),
				mDiffuseMapPath(diffusePath),
				mNormalMapPath(normalPath),
				mSpecularMapPath(specularPath) {

}

BuilderModelExternalMaps::~BuilderModelExternalMaps() {

}

BuilderModel& BuilderModelExternalMaps::setdiffusePath(std::string& path) {
	mDiffuseMapPath = path;
	return *this;
}

BuilderModel& BuilderModelExternalMaps::setNormalMapPath(std::string& path) {
	mNormalMapPath = path;
	return *this;
}

BuilderModel& BuilderModelExternalMaps::setSpecularMapPath(std::string& path) {
	mSpecularMapPath = path;
	return *this;
}

pModel BuilderModelExternalMaps::build() {
	return buildModel(mEngine, mProgram, mShapePath, mDiffuseMapPath,
			mNormalMapPath, mSpecularMapPath);
}

} /* models */
} /* fillwave */

