/*
 * IRenderer.cpp
 *
 *  Created on: Jan 31, 2016
 *      Author: filip
 */

#ifndef TESTS_MOCKS_IRENDERER_CPP_
#define TESTS_MOCKS_IRENDERER_CPP_

#pragma once

#include <fillwave/renderers/IRenderer.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace fillwave {
namespace framework {

class MockIRenderer : public IRenderer {
public:
  MOCK_METHOD1(update,
  void(IRenderable
  * renderable));
  MOCK_METHOD1(draw,
  void(ICamera
  & camera));
  MOCK_METHOD2(reset,
  void(GLuint
  width,
  GLuint height
  ));
  MOCK_METHOD0(clear,
  void());
};

}
}
#endif /* TESTS_MOCKS_IRENDERER_CPP_ */
