#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <array>
#include <string>

#include <MK/Core.hpp>
#include <MK/Graphics.hpp>

// Window Settings
constexpr unsigned int WINDOW_WIDTH  {800u};
constexpr unsigned int WINDOW_HEIGHT {600u};
const     std::string  WINDOW_TITLE  {"MK Engine"};

// Vertices and Indices
const std::array<GLfloat, 6 * 6> vertices =
{
  -0.5f,  -0.5f, 0.f, 1.f, 1.f, 1.f,
   0.0f,  -0.5f, 0.f, 1.f, 1.f, 1.f,
   0.5f,  -0.5f, 0.f, 1.f, 1.f, 1.f,
  -0.25f,  0.0f, 0.f, 1.f, 1.f, 1.f,
   0.25f,  0.0f, 0.f, 1.f, 1.f, 1.f,
   0.0f,   0.5f, 0.f, 1.f, 1.f, 1.f,
};
const std::array<GLuint, 9> indices =
{
  0, 1, 3,
  1, 2, 4,
  3, 4, 5,
};

int main()
{
  // Initializing GLFW
  mk::Core::initializeGLFW();

  // Creating a Window
  mk::Window window
  {
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    WINDOW_TITLE
  };

  // Initializing GLEW
  if (!mk::Core::initializeGLEW())
  {
    mk::Core::terminate();
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

  // Shader Program
  mk::Graphics::Shader defaultShader
  {
    "resources/Shaders/default.vert",
    "resources/Shaders/default.frag"
  };

  // VAO, VBO, and EBO
  mk::Graphics::VAO VAO;
  mk::Graphics::VBO VBO {vertices};
  mk::Graphics::EBO EBO {indices};

  VAO.Bind();
  VBO.Bind();
  EBO.Bind();

  VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
  VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

  VAO.Unbind();
  VBO.Unbind();
  EBO.Unbind();

  // Printing Engine and Version Info
  mk::Core::printEngineInfo();
  std::cout << '\n';
  mk::Core::printVersionInfo();

  // Line Mode
  mk::Graphics::useLineMode();

  // Vector Testing
  mk::Space::Vec3 vecOne {1.f, 2.f, -2.f};
  mk::Space::Vec3 vecTwo {4.f, -5.f, 3.f};
  mk::Debug::printVector(mk::Space::cross(vecOne, vecTwo));

  // Main Loop
  while (window.isOpen())
  {
    window.update();
    window.clear();
    defaultShader.Use();
    VAO.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
    window.render();
  }

  // Program Termination
  VAO.Delete();
  VBO.Delete();
  EBO.Delete();
  defaultShader.Delete();
  mk::Core::terminate();
  return EXIT_SUCCESS;
}
