/*
 * Cursor.cpp
 *
 *  Created on: Nov 6, 2014
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
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
 * filip.wasil@gmail.com
 *
 */

#include <fillwave/particles/Cursor.h>
#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/Fillwave.h>

namespace fillwave {
namespace particles {

Cursor::Cursor(Engine* engine,
               pTexture texture)
:Impostor(engine,
          FILLWAVE_ENDLESS,
          0.06,
          texture),
 mScreenFactor(GLfloat(engine->getScreenSize()[0]) / GLfloat(engine->getScreenSize()[1])) {

   loader::ProgramLoader loader;

   mProgram = loader.getCursor(engine);

   initUniformsCache();
}

Cursor::~Cursor() {

}

void Cursor::move(glm::vec2 position) {
   mProgram->use();
   core::Uniform::push(mULCPosition, position);
   core::Program::disusePrograms();
}

void Cursor::draw() {
   mProgram->use();

   core::Uniform::push(mULCScreenFactor, mScreenFactor);
   core::Uniform::push(mULCSize, mSize);

   coreDraw();

   core::Program::disusePrograms();
}

void Cursor::initUniformsCache() {
   mULCPosition = mProgram->getUniformLocation("uPosition");
   mULCScreenFactor = mProgram->getUniformLocation("uScreenFactor");
   mULCTextureUnit = mProgram->getUniformLocation("uTextureUnit");
   mULCSize = mProgram->getUniformLocation("uSize");

   mProgram->use();
   core::Uniform::push(mULCTextureUnit, FILLWAVE_DIFFUSE_UNIT);
   core::Program::disusePrograms();
}

} /* particles */
} /* fillwave */
