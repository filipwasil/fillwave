/*
 * BackendGLFW.cpp
 *
 *  Created on: Jan 8, 2015
 *      Author: filip
 */

#include "App.h"

#include <fillwave/Log.h>

FLOGINIT("BackendGLFW", FERROR | FFATAL)

flw::Engine *App::mGraphics;
GLfloat App::mScreenWidth;
GLfloat App::mScreenHeight;
GLFWwindow *App::mWindow;
GLFWwindow *App::mWindowNew;
GLuint App::mCursorPositionX;
GLuint App::mCursorPositionY;

App::App(int argc, char *argv[]) {

  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }

  mWindow = nullptr;
  mWindowNew = nullptr;

  mCursorPositionX = 1;
  mCursorPositionY = 1;

  windowInit(mWindow);

  App::mGraphics = new flw::Engine(argc, argv);
}

void App::windowInit(GLFWwindow *&window) {

  const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

  mScreenWidth = mode->width;
  mScreenHeight = mode->height;

  window = glfwCreateWindow(mScreenWidth, mScreenHeight, "Fillwave", glfwGetPrimaryMonitor(), NULL);

  glfwMakeContextCurrent(window);
  glfwWindowHint(GLFW_RED_BITS, 8);
  glfwWindowHint(GLFW_GREEN_BITS, 8);
  glfwWindowHint(GLFW_BLUE_BITS, 8);
  glfwWindowHint(GLFW_DEPTH_BITS, 16);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  if (!window) {
    fLogE("Could not create a new rendering window.\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSetFramebufferSizeCallback(window, resizeCallback);
  glfwSetKeyCallback(window, keyboardCallback);
  glfwSetScrollCallback(window, scrollCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);
  glfwSetCharCallback(window, characterCallback);
  glfwSetCursorPosCallback(window, cursorPositionCallback);
  glfwSetCursorEnterCallback(window, cursorEnterCallback);
}

void App::windowDeinit(GLFWwindow *&window) {
  glfwSetWindowShouldClose(window, GL_TRUE);
}

App::~App() {
  delete mGraphics;
  glfwSetFramebufferSizeCallback(mWindow, NULL);
  glfwSetKeyCallback(mWindow, NULL);
  glfwSetScrollCallback(mWindow, NULL);
  glfwSetMouseButtonCallback(mWindow, NULL);
  glfwSetCharCallback(mWindow, NULL);
  glfwSetCursorPosCallback(mWindow, NULL);
  glfwSetCursorEnterCallback(mWindow, NULL);
  glfwDestroyWindow(mWindow);
  glfwTerminate();
}

void App::cursorShow() {
  glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void App::cursorHide() {
  glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void App::render() {
  while (!glfwWindowShouldClose(mWindow)) {
    GLfloat timeSinceLastFrameInSec, now = glfwGetTime();
    if (mTimeExpired == 0.0f) {
      mTimeExpired = now;
    }
    timeSinceLastFrameInSec = now - mTimeExpired;
    mTimeExpired = now;

    mGraphics->drawWithLines(timeSinceLastFrameInSec);
//     mGraphics->drawLines(timeSinceLastFrameInSec);
//      mGraphics->drawPoints(timeSinceLastFrameInSec);

    glfwSwapBuffers(mWindow);
    glfwPollEvents();
  }
  mWindow = nullptr;
}

void App::resizeCallback(GLFWwindow * /*window*/, int width, int height) {//xxx todo
  mGraphics->insertResizeScreen(width, height);
}

GLuint App::getScreenWidth() {
  const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  return mode->width;
}

GLuint App::getScreenHeight() {
  const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  return mode->height;
}

void App::keyboardCallback(GLFWwindow * /*window*/, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE) {
    windowDeinit(mWindow);
  }

  /* And/Or provide it to Fillwave to executeall entity callbacks when focused */

  flw::flf::KeyboardEventData data;
  data.action = action;
  data.key = key;
  data.mode = mods;
  data.scanCode = scancode;
  flw::flf::KeyboardEvent event(data);
  mGraphics->insertInput(event);
}

void App::mouseButtonCallback(GLFWwindow * /*window*/, int button, int action, int mods) {
  flw::flf::MouseButtonEventData data;
  data.mWhereX = mCursorPositionX;
  data.mWhereY = mCursorPositionY;
  data.mAction = action;
  data.mButton = button;
  data.mMods = mods;
  flw::flf::MouseButtonEvent event(data);
  mGraphics->insertInput(event);
}

void App::scrollCallback(GLFWwindow * /*window*/, double xoffset, double yoffset) {
  flw::flf::ScrollEventData d;
  d.mOffsetX = xoffset;
  d.mOffsetY = yoffset;
  flw::flf::ScrollEvent event(d);
  mGraphics->insertInput(event);
}

void App::characterCallback(GLFWwindow * /*window*/, unsigned int ascii) {
  flw::flf::CharacterEventData d;
  d.character = ascii;
  flw::flf::CharacterEvent event(d);
  mGraphics->insertInput(event);
}

void App::cursorPositionCallback(GLFWwindow * /*window*/, double xpos, double ypos) {
  flw::flf::CursorPositionEventData d;
  if (xpos > mGraphics->getScreenSize()[0]) {
    glfwSetCursorPos(mWindow, mGraphics->getScreenSize()[0], ypos);
    d.xPosition = mGraphics->getScreenSize()[0];
  } else if (xpos < 0.0) {
    glfwSetCursorPos(mWindow, 0.0, ypos);
    d.xPosition = 0.0;
  } else {
    d.xPosition = xpos;
  }

  if (ypos > mGraphics->getScreenSize()[1]) {
    glfwSetCursorPos(mWindow, xpos, mGraphics->getScreenSize()[1]);
    d.yPosition = mGraphics->getScreenSize()[1];
  } else if (ypos < 0.0) {
    glfwSetCursorPos(mWindow, xpos, 0);
    d.yPosition = 0;
  } else {
    d.yPosition = ypos;
  }

  mCursorPositionX = xpos;
  mCursorPositionY = ypos;

  flw::flf::CursorPositionEvent event(d);
  mGraphics->insertInput(event);
}

void App::cursorEnterCallback(GLFWwindow * /*window*/, int in) {
  flw::flf::CursorEnterEventData d;
  d.direction = in;
  flw::flf::CursorEnterEvent event(d);
  mGraphics->insertInput(event);
}

void App::reload() {
  windowDeinit(mWindow);
  windowInit(mWindowNew);
  App::mGraphics->reload();
}
