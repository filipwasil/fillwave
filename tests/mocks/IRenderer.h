#pragma once

#include <fillwave/renderers/IRenderer.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace flw {
namespace flf {

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
