#include "../common.h"

#include <flw/Fillwave.h>

using namespace flw;
using namespace flw::flf;

#ifdef FILLWAVE_BACKEND_OPENGL_ES_PC
typedef void (*getProcAddr)(void);

void getProcMock(void) {
  // nothing
}

getProcAddr glfwGetProcAddress(const char* procname) {
  return &getProcMock;
}

EnginePCGLES* getEngine() {
  GLchar *const argv[] = {"0f0f "};
  return new EnginePCGLES(1, argv, glfwGetProcAddress);
}
#elif defined(FILLWAVE_BACKEND_OPENGL_ES_20) || defined(FILLWAVE_BACKEND_OPENGL_ES_30)
EngineAndroid* getEngine() {

}
#else
EnginePC* getEngine() {
  GLchar *const argv[] = {"0f0f "};
  return new EnginePC(1, argv);
}
#endif

TEST (Engine, texture) {
  auto engine = getEngine();
  auto texture = engine->storeTexture("data/text.png");
  auto empty = nullptr;
  EXPECT_EQ (texture, empty);
}
