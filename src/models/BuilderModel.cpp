/*
 * BuilderModel.cpp
 *
 *  Created on: Apr 26, 2015
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

#include <fillwave/models/BuilderModel.h>

#include <fillwave/Fillwave.h>

#include <fillwave/extras/Log.h>

FLOGINIT("BuilderModel", FERROR | FFATAL)

namespace fillwave {
namespace models {

BuilderModel::BuilderModel(Engine* engine,
                           std::string modelPath,
                           pProgram program):
   mEngine(engine),
   mProgram(program),
   mShapePath(modelPath) {
}

BuilderModel::~BuilderModel() {

}

pModel BuilderModel::build() {
   return buildModel(mEngine,
                     mProgram,
                     mShapePath);
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
