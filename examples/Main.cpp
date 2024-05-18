#include <stdlib.h>
#include <iostream>
#include <vector>
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

  // Player
  mk::Shapes::Rectangle player
  {
    {64.f, 64.f},
    64.f,
    64.f
  };
  player.setFillColor(mk::Color::Red);
  mk::Shapes::Rectangle zone
  {
    {192.f, 192.f},
    408.f,
    192.f
  };
  zone.setFillColor(mk::Color::Yellow);

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

    player.move(mk::Space::normalize({xFactor, yFactor}) * window.getDeltaTime() * 300.f);

    mk::Shapes::Collision::AABB(player.getBounds(), zone.getBounds())
      ? player.setFillColor(mk::Color::Blue)
      : player.setFillColor(mk::Color::Red);

    window.clear();

    shapeRenderer.use();
    shapeRenderer.render(zone);
    shapeRenderer.render(player);

    window.display();
  }

  // Program Termination
  defaultShader.Delete();
  mk::Core::terminate();
  return EXIT_SUCCESS;
}
