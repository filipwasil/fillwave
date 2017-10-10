/*
 * BackendGLFW.cpp
 *
 *  Created on: Jan 8, 2015
 *      Author: filip
 */

#include "ContextGLFW.h"

#include <fillwave/Log.h>

FLOGINIT("BackendGLFW", FERROR | FFATAL)

flw::Engine *App::mGraphics;
GLfloat App::mScreenWidth;
GLfloat App::mScreenHeight;
GLFWwindow *App::mWindow;
GLFWwindow *App::mWindowNew;
GLuint App::mCursorPositionX;
GLuint App::mCursorPositionY;
flw::flf::EventData App::mEventData;

ContextGLFW::ContextGLFW(int argc, char *argv[]) {

  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }

  mWindow = nullptr;
  mWindowNew = nullptr;

  mCursorPositionX = 1;
  mCursorPositionY = 1;

  windowInit(mWindow);

  ContextGLFW::mGraphicsEngine = new flw::Engine(argc, argv);
}

void ContextGLFW::windowInit(GLFWwindow *&window) {

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

void ContextGLFW::windowDeinit(GLFWwindow *&window) {
  glfwSetWindowShouldClose(window, GL_TRUE);
}

ContextGLFW::~ContextGLFW() {
  delete mGraphicsEngine;
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

void ContextGLFW::cursorShow() {
  glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void ContextGLFW::cursorHide() {
  glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void ContextGLFW::render() {
  while (!glfwWindowShouldClose(mWindow)) {
    GLfloat timeSinceLastFrameInSec, now = glfwGetTime();
    if (mTimeExpired == 0.0f) {
      mTimeExpired = now;
    }
    timeSinceLastFrameInSec = now - mTimeExpired;
    mTimeExpired = now;

    mGraphicsEngine->draw(timeSinceLastFrameInSec);
//      mGraphicsEngine->drawLines(timeSinceLastFrameInSec);
//      mGraphicsEngine->drawPoints(timeSinceLastFrameInSec);

    glfwSwapBuffers(mWindow);
    glfwPollEvents();
  }
  mWindow = nullptr;
}

void App::resizeCallback(GLFWwindow * /*window*/, int width, int height) {//xxx todo
  mGraphics->onResizeScreen(width, height);
}

GLuint ContextGLFW::getScreenWidth() {
  const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  return mode->width;
}

GLuint ContextGLFW::getScreenHeight() {
  const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  return mode->height;
}

void ContextGLFW::keyboardCallback(GLFWwindow * /*window*/, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE) {
    windowDeinit(mWindow);
  }

  /* And/Or provide it to Fillwave to executeall entity callbacks when focused */

  mEventData.mKey.action = action;
  mEventData.mKey.key = key;
  mEventData.mKey.mode = mods;
  mEventData.mKey.scanCode = scancode;
  flw::flf::Event event(flw::flf::eEventType::key, mEventData);
  mGraphics->onEvent(event);
}

void App::mouseButtonCallback(GLFWwindow * /*window*/, int button, int action, int mods) {
  mEventData.mMouseButton.mWhereX = mCursorPositionX;
  mEventData.mMouseButton.mWhereY = mCursorPositionY;
  mEventData.mMouseButton.mAction = action;
  mEventData.mMouseButton.mButton = button;
  mEventData.mMouseButton.mMods = mods;
  onEvent(flw::flf::eEventType::mouseButton);
}

void App::scrollCallback(GLFWwindow * /*window*/, double /*xoffset*/, double /*yoffset*/) {
//  mEventData.mOffsetX = xoffset;
//  mEventData.mOffsetY = yoffset;
//  mGraphics->onEvent(flw::flf::eEventType::scroll);
}

void App::characterCallback(GLFWwindow * /*window*/, unsigned int ascii) {
  mEventData.mChar.character = ascii;
  onEvent(flw::flf::eEventType::character);
}

void ContextGLFW::cursorPositionCallback(GLFWwindow * /*window*/, double xpos, double ypos) {
  flw::flf::CursorPositionEventData d;
  if (xpos > mGraphicsEngine->getScreenSize()[0]) {
    glfwSetCursorPos(mWindow, mGraphicsEngine->getScreenSize()[0], ypos);
    d.xPosition = mGraphicsEngine->getScreenSize()[0];
  } else if (xpos < 0.0) {
    glfwSetCursorPos(mWindow, 0.0, ypos);
    d.xPosition = 0.0;
  } else {
    d.xPosition = xpos;
  }

  if (ypos > mGraphicsEngine->getScreenSize()[1]) {
    glfwSetCursorPos(mWindow, xpos, mGraphicsEngine->getScreenSize()[1]);
    d.yPosition = mGraphicsEngine->getScreenSize()[1];
  } else if (ypos < 0.0) {
    glfwSetCursorPos(mWindow, xpos, 0);
    d.yPosition = 0;
  } else {
    d.yPosition = ypos;
  }

  mCursorPositionX = xpos;
  mCursorPositionY = ypos;

  onEvent(flw::flf::eEventType::cursorPosition);
}

void App::cursorEnterCallback(GLFWwindow * /*window*/, int in) {
  mEventData.mCursorEnter.direction = in;
  onEvent(flw::flf::eEventType::cursorEnter);
}

void App::onEvent(const flw::flf::eEventType& type) {
  mGraphics->onEvent(flw::flf::Event(type, mEventData));
}

void ContextGLFW::reload() {
  windowDeinit(mWindow);
  windowInit(mWindowNew);
  ContextGLFW::mGraphicsEngine->reload();
}
