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
  glPointSize(5.f);

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

  // Rectangle
  mk::Shapes::Rectangle rect
  {
    {32.f, 32.f},
    32.f,
    32.f,
  };

  // Printing Engine and Version Info
  mk::Core::printEngineInfo();
  std::cout << '\n';
  mk::Core::printVersionInfo();

  // Main Loop
  while (window.isOpen())
  {
    window.update();

    if (window.isKeyPressed(mk::Input::Key::C))
      mk::Graphics::usePointMode();
    else if (window.isKeyPressed(mk::Input::Key::V))
      mk::Graphics::useLineMode();
    else if (window.isKeyPressed(mk::Input::Key::B))
      mk::Graphics::useFillMode();

    window.clear();
    defaultShader.Use();

    mk::Space::Mat4 model {1.f};
    mk::Space::Mat4 view {1.f};
    mk::Space::Mat4 projection = mk::Space::ortho(
      0,
      (float)WINDOW_WIDTH,
      0,
      (float)WINDOW_HEIGHT,
      -1.f,
      1.f
    );

    defaultShader.SetMat4("model", model);
    defaultShader.SetMat4("view", view);
    defaultShader.SetMat4("projection", projection);

    window.draw(rect, defaultShader);
    window.render();
  }

  // Program Termination
  defaultShader.Delete();
  mk::Core::terminate();
  return EXIT_SUCCESS;
}
