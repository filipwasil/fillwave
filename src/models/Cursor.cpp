/*
 * Cursor.cpp
 *
 *  Created on: Nov 6, 2014
 *      Author: filip
 */

#include <fillwave/models/Cursor.h>
#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/Fillwave.h>

namespace fillwave {
namespace framework {

Cursor::Cursor(Engine* engine, pTexture texture) :
	Impostor(engine,
	         FILLWAVE_ENDLESS, 0.06, texture),
	mScreenFactor(
	    GLfloat(engine->getScreenSize()[0])
	    / GLfloat(engine->getScreenSize()[1])) {

	mProgram = ProgramLoader(engine).getCursor();

	initUniformsCache();
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

} /* framework */
pCursor buildCursor(Engine* engine, pTexture texture) {
	return std::make_shared < framework::Cursor > (engine, texture);
}
} /* fillwave */
