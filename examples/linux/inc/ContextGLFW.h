/*
 * ContextGLFW.h
 *
 *  Created on: Jan 8, 2015
 *      Author: filip
 */

#ifndef ContextGLFW_H_
#define ContextGLFW_H_

#include <fillwave/Fillwave.h>
#include <GLFW/glfw3.h>
#include <fillwave/Framework.h>

namespace fillwave {
class Engine;
}

class ContextGLFW {
private:
  GLfloat mTimeExpired = 0.0f;
  static GLuint mCursorPositionX;
  static GLuint mCursorPositionY;
public:
  ContextGLFW(int argc, char *argv[]);

  virtual ~ContextGLFW();

  void cursorShow();

  void cursorHide();

  void render();

  static fillwave::Engine *mGraphicsEngine;
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

#endif /* ContextGLFW_H_ */
