/*
 *  Created on: Jan 8, 2015
 *      Author: filip
 */

#include "ContextGLFW.h"

#include <flw/Log.h>

#include <flw/Config.h>

FLOGINIT_DEFAULT()

flw::Engine *ContextGLFW::mGraphics;
GLfloat ContextGLFW::mScreenWidth;
GLfloat ContextGLFW::mScreenHeight;
GLFWwindow *ContextGLFW::mWindow;
GLFWwindow *ContextGLFW::mWindowNew;
GLuint ContextGLFW::mCursorPositionX;
GLuint ContextGLFW::mCursorPositionY;
flw::flf::EventData ContextGLFW::mEventData;

ContextGLFW::ContextGLFW(int argc, char *argv[]) {

  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }

#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#elif defined(FILLWAVE_BACKEND_OPENGL_ES_30)
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#elif defined(FILLWAVE_BACKEND_OPENGL_45)
#endif

  mWindow = nullptr;
  mWindowNew = nullptr;

  mCursorPositionX = 1;
  mCursorPositionY = 1;

  windowInit(mWindow);

#if defined(FILLWAVE_BACKEND_OPENGL_ES_30) || defined(FILLWAVE_BACKEND_OPENGL_ES_20)
  ContextGLFW::mGraphics = new flw::EnginePCGLES(argc, argv, glfwGetProcAddress);
#else
  ContextGLFW::mGraphics = new flw::EnginePC(argc, argv);
#endif
}

void ContextGLFW::windowInit(GLFWwindow *&window) {

  const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

  mScreenWidth = mode->width;
  mScreenHeight = mode->height;

  // for presentation purposes
  int monitorsSize = 0;
  auto monitors = glfwGetMonitors(&monitorsSize);

  if (monitorsSize > 1) {
    window = glfwCreateWindow(mScreenWidth, mScreenHeight, "Fillwave", monitors[1], nullptr);
  } else if (monitorsSize == 1) {
    window = glfwCreateWindow(mScreenWidth, mScreenHeight, "Fillwave", monitors[0], nullptr);
  } else {
    // no monitors to get
  }

  glfwMakeContextCurrent(window);

#if defined(FILLWAVE_BACKEND_OPENGL_ES_20) || defined(FILLWAVE_BACKEND_OPENGL_ES_30)
#else
  glfwWindowHint(GLFW_RED_BITS, 8);
  glfwWindowHint(GLFW_GREEN_BITS, 8);
  glfwWindowHint(GLFW_BLUE_BITS, 8);
  glfwWindowHint(GLFW_DEPTH_BITS, 16);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

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
  glfwSetFramebufferSizeCallback(mWindow, nullptr);
  glfwSetKeyCallback(mWindow, nullptr);
  glfwSetScrollCallback(mWindow, nullptr);
  glfwSetMouseButtonCallback(mWindow, nullptr);
  glfwSetCharCallback(mWindow, nullptr);
  glfwSetCursorPosCallback(mWindow, nullptr);
  glfwSetCursorEnterCallback(mWindow, nullptr);
  glfwSetWindowShouldClose(window, GL_TRUE);
  glfwDestroyWindow(mWindow);
}

ContextGLFW::~ContextGLFW() {
  delete ContextGLFW::mGraphics;
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

    mEventData.mTime.timePassed = timeSinceLastFrameInSec;
    flw::flf::Event event(flw::flf::EEventType::time, mEventData);
    mGraphics->onEvent(event);

    mGraphics->draw();
//      mGraphics->drawLines(timeSinceLastFrameInSec);
//      mGraphics->drawPoints(timeSinceLastFrameInSec);

    glfwSwapBuffers(mWindow);
    glfwPollEvents();
  }
  mWindow = nullptr;
}

void ContextGLFW::resizeCallback(GLFWwindow * /*window*/, int width, int height) {
  if (mGraphics) {
    mGraphics->onResizeScreen(width, height);
  }
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
  mEventData.mKey.action = action;
  mEventData.mKey.key = key;
  mEventData.mKey.mode = mods;
  mEventData.mKey.scanCode = scancode;
  flw::flf::Event event(flw::flf::EEventType::key, mEventData);
  mGraphics->onEvent(event);

  if (key == GLFW_KEY_ESCAPE) {
    windowDeinit(mWindow);
  }
}

void ContextGLFW::mouseButtonCallback(GLFWwindow * /*window*/, int button, int action, int mods) {
  mEventData.mMouseButton.whereX = mCursorPositionX;
  mEventData.mMouseButton.whereY = mCursorPositionY;
  mEventData.mMouseButton.action = action;
  mEventData.mMouseButton.button = button;
  mEventData.mMouseButton.mods = mods;
  onEvent(flw::flf::EEventType::mouseButton);
}

void ContextGLFW::scrollCallback(GLFWwindow * /*window*/, double xoffset, double yoffset) {
  mEventData.mMouseScroll.offsetX = xoffset;
  mEventData.mMouseScroll.offsetY = yoffset;
  onEvent(flw::flf::EEventType::scroll);
}

void ContextGLFW::characterCallback(GLFWwindow * /*window*/, unsigned int ascii) {
  mEventData.mChar.character = ascii;
  onEvent(flw::flf::EEventType::character);
}

void ContextGLFW::cursorPositionCallback(GLFWwindow * /*window*/, double xpos, double ypos) {
  if (xpos > mGraphics->getScreenSize()[0]) {
    glfwSetCursorPos(mWindow, mGraphics->getScreenSize()[0], ypos);
    mEventData.mCursorPosition.xPosition = mGraphics->getScreenSize()[0];
  } else if (xpos < 0.0) {
    glfwSetCursorPos(mWindow, 0.0, ypos);
    mEventData.mCursorPosition.xPosition = 0.0;
  } else {
    mEventData.mCursorPosition.xPosition = xpos;
  }

  if (ypos > mGraphics->getScreenSize()[1]) {
    glfwSetCursorPos(mWindow, xpos, mGraphics->getScreenSize()[1]);
    mEventData.mCursorPosition.yPosition = mGraphics->getScreenSize()[1];
  } else if (ypos < 0.0) {
    glfwSetCursorPos(mWindow, xpos, 0);
    mEventData.mCursorPosition.yPosition = 0;
  } else {
    mEventData.mCursorPosition.yPosition = ypos;
  }

  mCursorPositionX = xpos;
  mCursorPositionY = ypos;

  onEvent(flw::flf::EEventType::cursorPosition);
}

void ContextGLFW::cursorEnterCallback(GLFWwindow * /*window*/, int in) {
  mEventData.mCursorEnter.direction = in;
  onEvent(flw::flf::EEventType::cursorEnter);
}

void ContextGLFW::onEvent(const flw::flf::EEventType& type) {
  mGraphics->onEvent(flw::flf::Event(type, mEventData));
}

void ContextGLFW::reload() {
  windowDeinit(mWindow);
  windowInit(mWindowNew);
  ContextGLFW::mGraphics->reload();
}