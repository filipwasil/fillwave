#include <fillwave/Fillwave.h>
#include <fillwave/Framework.h>
#include <GL/freeglut.h>
#include <memory>
#include "MountainConstructor.h"

#include <fillwave/Log.h>

using namespace flw;
using namespace flw::framework;
using namespace std;

FLOGINIT_DEFAULT()

Engine *mEngine;

pCameraPerspective gCamera;
pScenePerspective gScene;

flc::Program *gProgram;
map<string, pModel> gModels;

void init() {
  /* Scene */
  gScene = buildScenePerspective();

  /* Camera */
  gCamera = std::make_shared<CameraPerspective>(glm::vec3(0.0, 5.0, 0.0),
                                                glm::quat(),
                                                glm::radians(90.0),
                                                1.0,
                                                0.1,
                                                1000.0);

  /* Shaders */
  gProgram = ProgramLoader(mEngine).getDefault();

  /* Models */


  /* Lights */
  pLight light = mEngine->storeLightSpot(glm::vec3(1.0, 20.0, 6.0), glm::quat(), glm::vec4(1.0, 1.0, 1.0, 0.0));
  light->rotateTo(glm::vec3(1.0, 0.0, 0.0), glm::radians(-90.0));
}

void perform() {
  mEngine->configFPSCounter("fonts/Titania", glm::vec2(0.7, 0.9), 100.0);
  mEngine->setCurrentScene(gScene);

  pIEffect fog(new Fog());

  gScene->setCamera(gCamera);

  Material material;

  pMeshTerrain terrain = std::make_shared<MeshTerrain>(mEngine,
                                                       gProgram,
                                                       new MountainConstructor(),
                                                       material,
                                                       "textures/test.png",
                                                       "textures/testNormal.png",
                                                       "",
                                                       20,
                                                       16);
  terrain->scaleTo(2.0);
  terrain->addEffect(fog);
  gScene->attach(terrain);
}

void showDescription() {
  /* Description */
  pText hint0 = mEngine->storeText("Fillwave example terrain", "fonts/Titania", glm::vec2(-0.95, 0.80), 100.0);
  pText hint5 = mEngine->storeText("Use mouse to move the camera", "fonts/Titania", glm::vec2(-0.95, -0.40), 70.0);
  pText hint3 = mEngine->storeText("Use 'S' for camera back", "fonts/Titania", glm::vec2(-0.95, -0.50), 70.0);
  pText hint4 = mEngine->storeText("Use 'W' for camera forward", "fonts/Titania", glm::vec2(-0.95, -0.60), 70.0);
  pText hint1 = mEngine->storeText("Use 'T' to resume/stop time", "fonts/Titania", glm::vec2(-0.95, -0.70), 70.0);
  pText hint6 = mEngine->storeText("Use 'D' for toggle debugger On/Off",
                                   "fonts/Titania",
                                   glm::vec2(-0.95, -0.80),
                                   70.0);
}

void disp(void) {
  fLogE("display");
}

void timer(int) {
  static int Old = glutGet(GLUT_ELAPSED_TIME);
  int New = glutGet(GLUT_ELAPSED_TIME);
  int delta = New - Old;
  Old = New;

  mEngine->draw(static_cast<float>(delta) * 0.001f);

  glutSwapBuffers();

  glutTimerFunc(1.0f / 60.0f, timer, 1);
}

void resize(int width, int height) {
  mEngine->insertResizeScreen(width, height);
}


int main(int argc, char *argv[]) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

#ifdef FILLWAVE_GLES_3_0
  glutInitContextVersion(3, 0); /* OpenGL ES 3.0 */
#else
  glutInitContextVersion(3, 3); /* OpenGL 3.3 */
#endif
  glutInitContextFlags(GLUT_CORE_PROFILE | GLUT_DEBUG);

  glutInitWindowSize(960, 560);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
// apparentyly this function does not work in my version of freeglut
  glutDisplayFunc(disp);
  glutTimerFunc(100, timer, 1);
  glutReshapeFunc(resize);

  mEngine = new Engine(argc, argv);

  init();
  perform();
  showDescription();

  glutMainLoop();

  delete mEngine;

  return 0;
}
