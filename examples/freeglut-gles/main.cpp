#include <stdio.h>
#include <stdlib.h>

/* Ensure we are using opengl's core profile only */
#define GL3_PROTOTYPES 1
#include <fillwave/Fillwave.h>
#include <memory>

int main(int argc, char *argv[]) {

	std::unique_ptr<Engine> engine(new Engine(argc, argv));
	auto camera = make_shared < space::CameraPerspective
			> (glm::vec3(0.0, 0.0, 6.0), glm::quat());
	auto scene = buildScenePerspective(camera);
	engine->setCurrentScene(scene);
	engine->storeText("Fillwave SDL2 example", "FreeSans", -0.95f, 0.2f, 200.0f);

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	while (!quit) {
		float timePassed = 1.0f / 60.0f;
		engine->draw(timePassed);
	}

	engine.reset();

	return 0;
}
