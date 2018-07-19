#pragma once

/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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

  static void onEvent(const flw::flf::EEventType& type);

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
