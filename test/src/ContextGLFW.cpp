/*
 * BackendGLFW.cpp
 *
 *  Created on: Jan 8, 2015
 *      Author: filip
 */

#include <ContextGLFW.h>
#include <fillwave/extras/Log.h>

FLOGINIT("BackendGLFW", FERROR | FFATAL)

   fillwave::Engine* ContextGLFW::mGraphicsEngine;
   GLfloat ContextGLFW::mScreenWidth;
   GLfloat ContextGLFW::mScreenHeight;
   GLFWwindow* ContextGLFW::mWindow;
   GLFWwindow* ContextGLFW::mWindowNew;
   GLuint ContextGLFW::mCursorPositionX;
   GLuint ContextGLFW::mCursorPositionY;

ContextGLFW::ContextGLFW() {

   if (!glfwInit()) {
      exit(EXIT_FAILURE);
   }

   mWindow = nullptr;
   mWindowNew = nullptr;

   mCursorPositionX = 1;
   mCursorPositionY = 1;

   windowInit(mWindow);
}

void ContextGLFW::windowInit(GLFWwindow*& window) {

   const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

   mScreenWidth = mode->width;
   mScreenHeight = mode->height;

   window = glfwCreateWindow(mScreenWidth,
                              mScreenHeight,
                              "Fillwave",
                              glfwGetPrimaryMonitor(), /*NULL*/
                              NULL);

   glfwMakeContextCurrent(window);
   glfwWindowHint(GLFW_RED_BITS, 8);
   glfwWindowHint(GLFW_GREEN_BITS, 8);
   glfwWindowHint(GLFW_BLUE_BITS, 8);
   glfwWindowHint(GLFW_DEPTH_BITS, 16);

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//xxx sure ?

   if(!window) {
      FLOG_ERROR("Could not create a new rendering window.\n");
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

void ContextGLFW::windowDeinit(GLFWwindow*& window) {
   glfwSetWindowShouldClose(window, GL_TRUE);
}
ContextGLFW::~ContextGLFW() {
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

void ContextGLFW::resizeCallback(GLFWwindow* window,
                    int width,
                    int height) {//xxx todo
   mGraphicsEngine->insertResizeScreen(width, height);
}

GLuint ContextGLFW::getScreenWidth() {
   const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
   return mode->width;
}

GLuint ContextGLFW::getScreenHeight() {
   const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
   return mode->height;
}

void ContextGLFW::keyboardCallback(GLFWwindow* window,
                                   int key,
                                   int scancode,
                                   int action,
                                   int mods) {
   if (key ==  GLFW_KEY_ESCAPE)
      windowDeinit(mWindow);

   /* And/Or provide it to Fillwave to executeall entity callbacks when focused */

   fillwave::actions::KeyboardEventData data;
   data.action = action;
   data.key = key;
   data.mode = mods;
   data.scanCode = scancode;
   fillwave::actions::KeyboardEvent event(data);
   mGraphicsEngine->insertInputKey(event);
}

void ContextGLFW::mouseButtonCallback(GLFWwindow* window,
                         int button,
                         int action,
                         int mods) {
   fillwave::actions::MouseButtonEventData data;
   data.mWhereX = mCursorPositionX;
   data.mWhereY = mCursorPositionY;
   data.mAction = action;
   data.mButton = button;
   data.mMods = mods;
   fillwave::actions::MouseButtonEvent event(data);
   mGraphicsEngine->insertInputMouseButton(event);
//   if (GLFW_MOUSE_BUTTON_LEFT == button && GLFW_RELEASE == action)
//      reload();
//   ContextGLFW::mGraphicsEngine->insertResizeScreen(mScreenWidth,mScreenHeight);
}

void ContextGLFW::scrollCallback(GLFWwindow* window,
                    double xoffset,
                    double yoffset) {
   fillwave::actions::ScrollEventData d;
   d.mOffsetX = xoffset;
   d.mOffsetY = yoffset;
   fillwave::actions::ScrollEvent event(d);
   mGraphicsEngine->insertInputScroll(event);
}

void ContextGLFW::characterCallback(GLFWwindow* window,
                                     unsigned int ascii) {
   fillwave::actions::CharacterEventData d;
   d.character = ascii;
   fillwave::actions::CharacterEvent event(d);
   mGraphicsEngine->insertInputCharacter(event);
}

void ContextGLFW::cursorPositionCallback(GLFWwindow* window,
                                          double xpos,
                                          double ypos) {
   fillwave::actions::CursorPositionEventData d;
   if (xpos > mGraphicsEngine->getScreenSize()[0]) {
      glfwSetCursorPos (mWindow, mGraphicsEngine->getScreenSize()[0], ypos);
      d.xPosition = mGraphicsEngine->getScreenSize()[0];
   } else if (xpos < 0.0) {
      glfwSetCursorPos (mWindow,0.0, ypos);
      d.xPosition = 0.0;
   } else {
      d.xPosition = xpos;
   }

   if (ypos > mGraphicsEngine->getScreenSize()[1]) {
      glfwSetCursorPos (mWindow, xpos, mGraphicsEngine->getScreenSize()[1]);
      d.yPosition = mGraphicsEngine->getScreenSize()[1];
   } else if (ypos < 0.0 ) {
      glfwSetCursorPos (mWindow, xpos, 0);
      d.yPosition = 0;
   } else {
      d.yPosition = ypos;
   }

   mCursorPositionX = xpos;
   mCursorPositionY = ypos;

   fillwave::actions::CursorPositionEvent event(d);
   mGraphicsEngine->insertInputCursorPosition(event);
}

void ContextGLFW::cursorEnterCallback(GLFWwindow* window,
                         int in) {
   fillwave::actions::CursorEnterEventData d;
   d.direction = in;
   fillwave::actions::CursorEnterEvent event(d);
   mGraphicsEngine->insertInputCursorEnter(event);
}

void ContextGLFW::reload() {
   windowDeinit(mWindow);
   windowInit(mWindowNew);
   ContextGLFW::mGraphicsEngine->reload();
}
