#include "../common.h"

#include <fillwave/Fillwave.h>

using namespace flw;
using namespace flw::flf;

TEST (Engine, texture) {
  GLchar *const argv[] = {"0f0f "};
  auto engine = make_pu<EnginePC>(1, argv);
  auto texture = engine->storeTexture("data/text.png");
  auto empty = nullptr;
  EXPECT_EQ (texture, empty);
}
