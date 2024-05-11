#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include <MK/Graphics.hpp>

// Constants
constexpr unsigned int WINDOW_WIDTH  {800u};
constexpr unsigned int WINDOW_HEIGHT {600u};
const     std::string  WINDOW_TITLE  {"MK Engine"};

int main()
{
  // Initializing GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

  // Creating a Window
  GLFWwindow* window = glfwCreateWindow(
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    WINDOW_TITLE.c_str(),
    NULL,
    NULL
  );
  if (window == nullptr)
  {
    std::cerr << "Failed to create a GLFW window!\n";
    glfwTerminate();
    return EXIT_FAILURE;
  }
  glfwMakeContextCurrent(window);

  // Initializing GLEW
  GLenum glewErr = glewInit();
  if (glewErr != GLEW_OK)
  {
    std::cerr << "Failed to initialize GLEW!\n";
    std::cerr << "Error: " << glewGetErrorString(glewErr) << '\n';
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_FAILURE;
  }

  // Clear Color
  mk::Color::RGBA clearColor {0, 0, 0, 1.f};
  glClearColor(
    clearColor.red,
    clearColor.green,
    clearColor.blue,
    clearColor.alpha
  );

  // Main Loop
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
  }

  // Program Termination
  glfwDestroyWindow(window);
  glfwTerminate();
  return EXIT_SUCCESS;
}
