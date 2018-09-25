#include <stdio.h>
#include <stdlib.h>

/* Ensure we are using opengl's core profile only */
#define GL3_PROTOTYPES 1

#include <flw/Fillwave.h>
#include <memory>

#include <SDL.h>

#define PROGRAM_NAME "Fillwave test"

using namespace flw;
using namespace std;

/* A simple function that prints a message, the error code returned by SDL,
 * and quits the application */
void sdldie(const char *msg) {
  printf("%s: %s\n", msg, SDL_GetError());
  SDL_Quit();
  exit(1);
}

void checkSDLError(int line = -1) {
#ifndef NDEBUG
  const char *error = SDL_GetError();
  if (*error != '\0') {
    printf("SDL Error: %s\n", error);
    if (line != -1) {
      printf(" + line: %i\n", line);
    }
    SDL_ClearError();
  }
#endif
}

int main(int argc, char *argv[]) {
  SDL_Window *mainwindow;
  SDL_GLContext maincontext;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    sdldie("Unable to initialize SDL");
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  /* Create our window centered at 512x512 resolution */
  mainwindow = SDL_CreateWindow(PROGRAM_NAME,
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                960,
                                600,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (!mainwindow) {
    sdldie("Unable to create window");
  }

  checkSDLError(__LINE__);

  maincontext = SDL_GL_CreateContext(mainwindow);
  checkSDLError(__LINE__);

  /* Swap buffer synchronized with the monitor's vertical refresh */
  SDL_GL_SetSwapInterval(1);

  std::unique_ptr<Engine> engine(new Engine(argc, argv));
  auto camera = make_shared<space::CameraPerspective>(glm::vec3(0.0, 0.0, 6.0), glm::quat());
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

    SDL_GL_SwapWindow(mainwindow);

    while (SDL_PollEvent(&e) != 0) {
      //User requests quit
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
  }

  engine.reset();

  /* Delete our opengl context, destroy our window, and shutdown SDL */
  SDL_GL_DeleteContext(maincontext);
  SDL_DestroyWindow(mainwindow);
  SDL_Quit();

  return 0;
}
