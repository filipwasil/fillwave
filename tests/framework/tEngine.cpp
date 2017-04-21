#include <fillwave/Log.h>
#include <fillwave/Fillwave.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace flw;
using namespace flw::flf;

TEST (Engine, texture
) {
GLchar *const argv[] = {"0f0f "};
Engine *engine = new Engine(1, argv);
flc::Texture2D *texture = engine->storeTexture("data/text.png");
flc::Texture2D *empty = nullptr;
EXPECT_EQ (texture, empty
);
delete
engine;
}
