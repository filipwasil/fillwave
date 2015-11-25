
#include <fillwave/Fillwave.h>
#include <GL/freeglut.h>
#include <memory>

using namespace fillwave;
using namespace std;

Engine* gEngine;

void disp(void) {

	float timePassed = 1.0f / 60.0f;
	gEngine->draw(timePassed);

	glutSwapBuffers();
}

int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

#ifdef FILLWAVE_GLES_3_0
   glutInitContextVersion (3, 0); /* OpenGL ES 3.0 */
#else
   glutInitContextVersion (3, 3); /* OpenGL 3.3 */
#endif
   glutInitContextFlags (GLUT_CORE_PROFILE | GLUT_DEBUG);

   glutInitWindowSize (960, 560);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
	glutDisplayFunc(disp);

	gEngine = new Engine(argc, argv);
	auto camera = make_shared < space::CameraPerspective
			> (glm::vec3(0.0, 0.0, 6.0), glm::quat());
	auto scene = buildScenePerspective(camera);
	gEngine->setCurrentScene(scene);
	gEngine->storeText("Fillwave freeglut example", "FreeSans", -0.95f, 0.2f,
			100.0f);

	glutMainLoop();

	delete gEngine;

	return 0;
}
