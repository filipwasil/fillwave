
#include <fillwave/Fillwave.h>
#include <fillwave/extras/Debugger.h>
#include <GL/freeglut.h>
#include <memory>

#include <fillwave/extras/Log.h>

using namespace fillwave;
using namespace fillwave::actions;
using namespace std;

FLOGINIT_DEFAULT()

Engine* engine;

void disp(void) {
	float timePassed = 1.0f / 60.0f;
	engine->draw(timePassed);
	glutSwapBuffers();
}

void timer(int) {

	float timePassed = 1.0f / 60.0f;
	engine->draw(timePassed);
	glutSwapBuffers();

	glutTimerFunc(1.0f / 60.0f, timer, 1);
}

int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

#ifdef FILLWAVE_GLES_3_0
	glutInitContextVersion(3, 0); /* OpenGL ES 3.0 */
#else
	glutInitContextVersion (3, 3); /* OpenGL 3.3 */
#endif
	glutInitContextFlags(GLUT_CORE_PROFILE | GLUT_DEBUG);

	glutInitWindowSize(960, 560);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(disp);
	glutTimerFunc(100, timer, 1);

	engine = new Engine(argc, argv);
	auto camera =
			make_shared < space::CameraPerspective
					> (glm::vec3(0.0, 0.0, 6.0), glm::quat(), glm::radians(90.0), 1.0, 0.1, 1000.0);
	auto scene = buildScenePerspective(camera);
	engine->setCurrentScene(scene);
	engine->storeText("Fillwave freeglut example", "FreeSans", -0.95f, 0.2f,
			100.0f);

	//engine->configureDebugger(eDebuggerState::eLightsSpot);

	const GLint SPHERES = 5;
	pModel gSpheres[SPHERES];
	LoopCallback* loop[SPHERES];

	/* Program */
	loader::ProgramLoader loader;
	pProgram progDefault = loader.getDefault(engine);

	/* Lights */
	engine->storeLightSpot(glm::vec3(0.0, 0.0, 5.0), glm::quat(),
			glm::vec4(0.0, 1.0, 0.0, 0.0));

	/* Models */

	pModel wall = buildModel(engine, progDefault, "meshes/floor.obj",
			"textures/test.png", "textures/test.png", "textures/test.png");

	scene->attach(wall);

	models::BuilderModelExternalMaps builder(engine, "meshes/sphere.obj",
			progDefault, "textures/test.png");

	for (GLint i = 0; i < SPHERES; i++) {
		/* build */
		gSpheres[i] = builder.build(); //buildModel(engine, progDefault, "meshes/sphere.obj", "textures/test.png");

		/* move */
		gSpheres[i]->scaleTo(0.1);
		gSpheres[i]->moveByX(-4 + 2 * i);

		/* create callbacks loop */
		TimedScaleCallback* scaleUp = new TimedScaleCallback(gSpheres[i],
				0.1 * 2.0, 2.0f + i * 0.5);
		TimedScaleCallback* scaleDown = new TimedScaleCallback(gSpheres[i],
				0.1 * 1.0, 2.0f + i * 0.5);
		TimedRotateCallback* rotateLeft = new TimedRotateCallback(gSpheres[i],
				glm::vec3(0.0, 1.0, 0.0), glm::radians(90.0f), 2.0f + i * 0.5);
		TimedRotateCallback* rotateRight = new TimedRotateCallback(gSpheres[i],
				glm::vec3(0.0, 1.0, 0.0), glm::radians(90.0f), 2.0f + i * 0.5);
		TimedMoveCallback* moveUp = new TimedMoveCallback(gSpheres[i],
				glm::vec3(0.0, 1.0, 0.0), 2.0f + i * 0.5);
		TimedMoveCallback* moveDown = new TimedMoveCallback(gSpheres[i],
				glm::vec3(0.0, -1.0, 0.0), 2.0f + i * 0.5);

		SequenceCallback* sequence = new SequenceCallback();
		sequence->push_back(scaleUp);
		sequence->push_back(scaleDown);
		sequence->push_back(rotateLeft);
		sequence->push_back(rotateRight);
		sequence->push_back(moveUp);
		sequence->push_back(moveDown);

		if (i == SPHERES / 2) {
			TimedMoveCallback* moveBack = new TimedMoveCallback(gSpheres[i],
					glm::vec3(1.0, -1.0, 0.0), 2.0f + i * 0.5);
			TimedMoveCallback* moveFront = new TimedMoveCallback(gSpheres[i],
					glm::vec3(1.0, -1.0, 0.0), 2.0f + i * 0.5);
			sequence->push_back(moveBack);
			sequence->push_back(moveFront);
		}

		loop[i] = new LoopCallback(sequence, FILLWAVE_ENDLESS);

		gSpheres[i]->attachHierarchyCallback(loop[i]);

		scene->attach(gSpheres[i]);
	}

	wall->rotateByX(glm::radians(90.0));
	wall->moveInDirection(glm::vec3(0.0, -10.0, 0.0));
	wall->scaleTo(3.0);

	glutMainLoop();

	delete engine;

	return 0;
}
