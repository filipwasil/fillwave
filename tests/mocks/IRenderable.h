#pragma once

#include "../common.h"

#include <fillwave/models/base/IRenderable.h>
#include <fillwave/models/base/RenderItem.h>

using namespace flw;
using namespace flw::flf;

class MockIRenderable : public IRenderable {
public:
  MOCK_METHOD1(getRenderItem, bool(RenderItem& item));
  MOCK_METHOD1(updateRenderer, void(ICamera& camera));
  MOCK_METHOD1(draw, void(ICamera& camera));
  MOCK_METHOD1(drawPBRP, void(ICamera& camera));
  MOCK_METHOD1(drawDR, void(ICamera& camera));
  MOCK_METHOD1(drawDepth, void(ICamera& camera));
  MOCK_METHOD2(drawDepthColor, void(ICamera& camera, glm::vec3 &color));
  MOCK_METHOD1(drawAOG, void(ICamera& camera));
  MOCK_METHOD1(drawAOC, void(ICamera& camera));
  MOCK_METHOD1(drawOcclusionBox, void(ICamera& camera));
  MOCK_METHOD1(drawPicking, void(ICamera& camera));
  MOCK_METHOD1(updateRenderer, void(IRenderer& renderer));
};
