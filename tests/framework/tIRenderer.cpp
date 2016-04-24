/*
 * Engine.cpp
 *
 *  Created on: Jan 20, 2016
 *      Author: filip
 */

#include <fillwave/Log.h>
#include "../mocks/IRenderer.h"
#include "../mocks/IRenderable.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

FLOGINIT_DEFAULT()

using namespace fillwave;
using namespace fillwave::framework;

TEST (IRenderer, adding) {
	MockIRenderer renderer();
	MockIRenderable renderable();
}
