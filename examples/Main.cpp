#include <stdlib.h>
#include <iostream>
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

  // Square
  mk::Shapes::Rectangle square
  {
    {184.f, 184.f},
    32.f,
    32.f
  };
  square.setFillColor(mk::Color::Green);
  square.setScaleX(2.f);

  // Fullscreen Logic
  bool fullscreenPressed {false};

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

    window.clear();
    defaultShader.Use();

    camera.updateMatrix();
    camera.applyMatrix(defaultShader);

    shapeRenderer.render(square);

    window.display();
  }

  // Program Termination
  defaultShader.Delete();
  mk::Core::terminate();
  return EXIT_SUCCESS;
}
