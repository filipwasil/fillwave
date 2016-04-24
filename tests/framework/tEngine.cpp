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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"
	GLchar* const argv[] = {"0f0f "} ;
#pragma GCC diagnostic pop
	Engine* engine = new Engine(1, argv);
	core::Texture2D* texture = engine->storeTexture("data/text.png");
	core::Texture2D* empty = nullptr;
	EXPECT_EQ (texture, empty);
	delete engine;
}