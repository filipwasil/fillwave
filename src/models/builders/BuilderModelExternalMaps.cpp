/*
 * BuilderModelExternalMaps.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: filip
 */

#include <fillwave/models/builders/BuilderModelExternalMaps.h>
#include <fillwave/common/Macros.h>

FLOGINIT("BuilderModelExternalMaps", FERROR | FFATAL)

namespace fillwave {
namespace framework {

BuilderModelExternalMaps::BuilderModelExternalMaps(
   Engine* engine,
   std::string modelPath,
   core::Program* program,
   std::string diffusePath,
   std::string normalPath,
   std::string specularPath) :
	BuilderModel(engine, modelPath, program),
	mDiffuseMapPath(diffusePath),
	mNormalMapPath(normalPath),
	mSpecularMapPath(specularPath) {

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

puModel BuilderModelExternalMaps::build() {
	return make_unique<Model>(mEngine, mProgram, mShapePath, mDiffuseMapPath,
	                          mNormalMapPath, mSpecularMapPath);
}

} /* framework */
} /* fillwave */

