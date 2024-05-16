#include <stdlib.h>
#include <iostream>
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
  mk::Color::RGBA clearColor {mk::Color::Black};

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

    float xFactor {0.f};
    float yFactor {0.f};

    if (window.isKeyPressed(mk::Input::Key::W))
      yFactor -= 1.f;
    if (window.isKeyPressed(mk::Input::Key::S))
      yFactor += 1.f;
    if (window.isKeyPressed(mk::Input::Key::A))
      xFactor -= 1.f;
    if (window.isKeyPressed(mk::Input::Key::D))
      xFactor += 1.f;

    rect.move(mk::Space::normalize({xFactor, yFactor}) * window.getDeltaTime() * 100.f);

    window.clear();
    defaultShader.Use();

    camera.updateMatrix();
    camera.applyMatrix(defaultShader);

    shapeRenderer.render(rect);
    window.display();
  }

  // Program Termination
  defaultShader.Delete();
  mk::Core::terminate();
  return EXIT_SUCCESS;
}
