/*
 * BuilderModel.cpp
 *
 *  Created on: Apr 26, 2015
 *      Author: filip
 */

#include <fillwave/models/BuilderModel.h>

#include <fillwave/Fillwave.h>

#include <fillwave/extras/Log.h>

FLOGINIT("BuilderModel", FERROR | FFATAL)

namespace fillwave {
namespace models {

BuilderModel::BuilderModel(
		Engine* engine,
		std::string modelPath,
		pProgram program)
		: mEngine(engine), mProgram(program), mShapePath(modelPath) {
}

pModel BuilderModel::build() {
	return buildModel(mEngine, mProgram, mShapePath);
}

BuilderModel& BuilderModel::setModelPath(std::string& path) {
	mShapePath = path;
	return *this;
}

BuilderModel& BuilderModel::setProgram(pProgram program) {
	mProgram = program;
	return *this;
}

} /* models */
} /* fillwave */
