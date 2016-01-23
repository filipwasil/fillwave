/*
 * Engine.cpp
 *
 *  Created on: Jan 20, 2016
 *      Author: filip
 */

#include <fillwave/Log.h>
#include <fillwave/Fillwave.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

FLOGINIT_DEFAULT()

using namespace fillwave;
using namespace fillwave::framework;

TEST (Engine, texture) {
	GLchar* const argv[]= {"./"};
	Engine* engine = new Engine(1, argv);
	pTexture2D texture = engine->storeTexture("data/text.png");
	pTexture2D empty;
	EXPECT_EQ (texture, empty);
	texture.reset();
	delete engine;
}
