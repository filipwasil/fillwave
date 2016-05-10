/*
 * BuilderModel.cpp
 *
 *  Created on: Apr 26, 2015
 *      Author: filip
 */

#include <fillwave/models/builders/BuilderModel.h>

#include <fillwave/Fillwave.h>

#include <fillwave/Log.h>

FLOGINIT("BuilderModel", FERROR | FFATAL)

namespace fillwave {
namespace framework {

BuilderModel::BuilderModel(
   Engine* engine,
   std::string modelPath,
   core::Program* program) :
	mEngine(engine), mProgram(program), mShapePath(modelPath) {
}

puModel BuilderModel::build() {
	return std::make_unique<Model>(mEngine, mProgram, mShapePath);
}

BuilderModel& BuilderModel::setModelPath(std::string& path) {
	mShapePath = path;
	return *this;
}

BuilderModel& BuilderModel::setProgram(core::Program* program) {
	mProgram = program;
	return *this;
}

} /* framework */
} /* fillwave */
