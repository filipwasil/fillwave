#include <fillwave/Framework.h>
#include <fillwave/Fillwave.h>
#include <GLFW/glfw3.h>
#include <fillwave/Profiler.h>
#include <fillwave/Log.h>

FLOGINIT_DEFAULT()

typedef std::pair<std::string, float> result;
std::vector<result> mResults;

int initContext() {

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    GLfloat screenWidth = 800;
    GLfloat screenHeight = 800;
    GLFWwindow* window;
    GLFWwindow* mWindowNew;
    GLuint mCursorPositionX;
    GLuint mCursorPositionY;

    window = nullptr;
    mWindowNew = nullptr;

    mCursorPositionX = 1;
    mCursorPositionY = 1;

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    screenWidth = mode->width;
    screenHeight = mode->height;

    window = glfwCreateWindow(screenWidth,
                              screenHeight,
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
}

void printResults() {
    for (auto& it : mResults) {
        FLOG_USER("%s : %f ms", it.first.c_str(), it.second*0.000001);
    }
}

int main(int argc, char* argv[]) {
    initContext();

    auto start = FILLWAVE_MEASURE_START();
    fillwave::Engine* engine = new fillwave::Engine(argc, argv);
    mResults.push_back(result("Creating engine", FILLWAVE_MEASURE_STOP_GET(start)));

    start = FILLWAVE_MEASURE_START();
    delete engine;
    mResults.push_back(result("Deleting engine", FILLWAVE_MEASURE_STOP_GET(start)));

    printResults();

    return 0;
}