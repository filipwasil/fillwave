#include <GLFW/glfw3.h>
#include <cstdlib>

int initContext() {

  if (!glfwInit()) {
    exit(1);
  }

  GLfloat screenWidth = 800;
  GLfloat screenHeight = 800;
  GLFWwindow *window;
  GLFWwindow *mWindowNew;
  GLuint mCursorPositionX;
  GLuint mCursorPositionY;

  window = nullptr;
  mWindowNew = nullptr;

  mCursorPositionX = 1;
  mCursorPositionY = 1;

  const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

  screenWidth = mode->width;
  screenHeight = mode->height;

  window = glfwCreateWindow(screenWidth, screenHeight, "Fillwave", glfwGetPrimaryMonitor(), NULL);

  glfwMakeContextCurrent(window);
  glfwWindowHint(GLFW_RED_BITS, 8);
  glfwWindowHint(GLFW_GREEN_BITS, 8);
  glfwWindowHint(GLFW_BLUE_BITS, 8);
  glfwWindowHint(GLFW_DEPTH_BITS, 16);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  if (!window) {
    glfwTerminate();
    exit(1);
  }
}