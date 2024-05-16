#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

#include <MK/Core.hpp>
#include <MK/Graphics.hpp>

// Window Settings
constexpr unsigned int WINDOW_WIDTH  {400u};
constexpr unsigned int WINDOW_HEIGHT {400u};
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
  glPointSize(3.f);

  // Clear Color
  mk::Color::RGBA clearColor {mk::Color::Black};

  // Shader Program
  mk::Graphics::Shader defaultShader
  {
    "resources/Shaders/default.vert",
    "resources/Shaders/default.frag"
  };

  // Rectangle
  std::vector<mk::Shapes::Rectangle> rectangles;
  for (int y = 0; y < 8; y++)
    for (int x = 0; x < 8; x++)
    {
      rectangles.emplace_back(mk::Shapes::Rectangle(
        {x * 50.f, y * 50.f},
        50.f,
        50.f
      ));
      rectangles.back().setFillColor(
        ((y % 2 ? 0 : 1) + x) % 2 ? mk::Color::RGBA(237, 183, 173, 1.f) : mk::Color::RGBA(199, 81, 60, 1.f)
      );
    }

  // Printing Engine and Version Info
  mk::Core::printEngineInfo();
  std::cout << '\n';
  mk::Core::printVersionInfo();

  // Renderers
  mk::Render::Renderer shapeRenderer {defaultShader};

  // Camera
  mk::Camera2D camera
  {
    window.getBufferDimensions(),
    -1.f,
    1.f
  };

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

    camera.updateMatrix();
    camera.applyMatrix(defaultShader);

    for (const auto& rectangle : rectangles)
      shapeRenderer.render(rectangle);

    window.display();
  }

  // Program Termination
  defaultShader.Delete();
  mk::Core::terminate();
  return EXIT_SUCCESS;
}
