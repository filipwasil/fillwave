#pragma once

#include <fillwave/Fillwave.h>
#include <GLFW/glfw3.h>
#include <fillwave/Framework.h>

namespace flw {
class Engine;
}

class ContextGLFW {
private:
  GLfloat mTimeExpired = 0.0f;

  static GLuint mCursorPositionX;

  static GLuint mCursorPositionY;

  static flw::flf::EventData mEventData;

  static void onEvent(const flw::flf::eEventType& type);

public:
  ContextGLFW(int argc, char *argv[]);

  virtual ~ContextGLFW();

  static void cursorShow();

  static void cursorHide();

  void render();

  static flw::Engine *mGraphics;
  static GLFWwindow *mWindow;
  static GLFWwindow *mWindowNew;
  static GLfloat mScreenWidth;
  static GLfloat mScreenHeight;

  GLuint getScreenWidth();

  GLuint getScreenHeight();

  static void windowInit(GLFWwindow *&window);

  static void windowDeinit(GLFWwindow *&window);

  static void resizeCallback(GLFWwindow *w, int width, int height);

  static void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

  static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

  static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

  static void characterCallback(GLFWwindow *window, unsigned int ascii);

  static void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos);

  static void cursorEnterCallback(GLFWwindow *window, int in);

  static void reload();
};
