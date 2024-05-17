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
  window.setClearColor({24, 24, 24, 1.f});

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

  // Printing Engine and Version Info
  mk::Core::printEngineInfo();
  std::cout << '\n';
  mk::Core::printVersionInfo();

  // Camera
  mk::Camera2D camera
  {
    window.getBufferDimensions(),
    -1.f,
    1.f
  };

  // Renderers
  mk::Render::Renderer shapeRenderer {defaultShader, camera};

  // Square
  mk::Shapes::Rectangle square
  {
    {896.f, 476.f},
    128.f,
    128.f
  };
  square.setFillColor(mk::Color::Green);

  // Fullscreen Logic
  bool fullscreenPressed {false};

  // Adding Renderer to the Window
  window.addRenderer(shapeRenderer);

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

    if (window.isKeyPressed(mk::Input::Key::F))
    {
      if (!fullscreenPressed)
      {
        window.getIsMaximized()
          ? window.unmaximize()
          : window.maximize();
        fullscreenPressed = true;
      }
    }
    else
    {
      fullscreenPressed = false;
    }

    square.rotate(30.f * window.getDeltaTime());
    square.setScale({
      2 - (std::sin(window.getTime()) + 1.f) / 2.f,
    });

    window.clear();

    shapeRenderer.use();
    shapeRenderer.render(square);

    window.display();
  }

  // Program Termination
  defaultShader.Delete();
  mk::Core::terminate();
  return EXIT_SUCCESS;
}
