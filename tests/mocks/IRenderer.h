#pragma once

#include "../common.h"

#include <flw/flc/renderers/IRenderer.h>

namespace flw {
namespace flc {

class MockIRenderer : public IRenderer {
public:
  MOCK_METHOD1(update, void(IRenderable* renderable));
  MOCK_METHOD1(draw, void(ICamera& camera));
  MOCK_METHOD2(reset, void(GLuint width, GLuint height ));
  MOCK_METHOD0(clear, void());
};

}
}
