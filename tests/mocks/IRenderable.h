/*
 * IRenderable.h
 *
 *  Created on: Jan 31, 2016
 *      Author: filip
 */

#ifndef TESTS_MOCKS_IRENDERABLE_H_
#define TESTS_MOCKS_IRENDERABLE_H_

#pragma once

#include <fillwave/renderers/IRenderer.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace fillwave;
using namespace fillwave::framework;

class MockIRenderable: public IRenderable {
public:
	MOCK_METHOD1(getRenderItem, void(RenderItem& item));
	MOCK_METHOD1(updateRenderer, void(IRenderer& renderer));
};

#endif /* TESTS_MOCKS_IRENDERABLE_H_ */
