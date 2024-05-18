#ifndef MK_WINDOW_HPP
#define MK_WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

#include "Color.hpp"
#include "Render.hpp"
#include "Shapes.hpp"

namespace mk
{
  /**
   * @brief A class representing a window.
   */
  class Window
  {
    public:
      /**
       * @brief Default constructor.
       */
      Window()
      { _initialize(); }
      /**
       * @brief Constructor with specified dimensions and title.
       * @param width  The width of the window.
       * @param height The height of the window.
       * @param title  The title of the window.
       */
      Window(const unsigned int width, const unsigned int height, const std::string& title)
      : width(width), height(height), title(title)
      { _initialize(); }

      /**
       * @brief Gets the width of the window.
       * @return The width of the window.
       */
      unsigned int getWidth() const
      { return width; }
      /**
       * @brief Gets the height of the window.
       * @return The height of the window.
       */
      unsigned int getHeight() const
      { return height; }
      /**
       * @brief Gets the buffer dimensions of the window.
       * @return The buffer dimensions as a 2D vector.
       */
      mk::Space::Vec2 getBufferDimensions() const
      {
        return
        {
          (float)width,
          (float)height,
        };
      }
      /**
       * @brief Gets the title of the window.
       * @return The title of the window.
       */
      std::string getTitle() const
      { return title; }
      /**
       * @brief Gets the clear color of the window.
       * @return The clear color of the window.
       */
      mk::Color::RGBA getClearColor() const
      { return clearColor; }
      /**
       * @brief Gets the time elapsed since GLFW was initialized.
       * @return The time elapsed since GLFW was initialized, in seconds.
       */
      float getTime() const
      { return static_cast<float>(glfwGetTime()); }
      /**
       * @brief Gets the time taken to render the last frame.
       * @return The time taken to render the last frame, in seconds.
       */
      float getDeltaTime() const
      { return deltaTime; }
      /**
       * @brief Gets the frames per second (FPS) of the rendering.
       * @return The frames per second (FPS) of the rendering. If delta time is zero, returns zero.
       */
      float getFPS() const
      { return deltaTime > 0.f ? 1.f / deltaTime : 0.f; }
      /**
       * @brief Checks if the window is maximized.
       * @return True if the window is maximized, false otherwise.
       */
      bool getIsMaximized() const
      { return isMaximized; }
      /**
       * @brief Retrieves the list of renderers.
       * @return A vector containing pointers to the renderers.
       */
      std::vector<mk::Render::Renderer*> getRenderers() const
      { return renderers; }

      /**
       * @brief Sets the buffer dimensions of the window.
       * @param bufferDimensions The new buffer dimensions.
       */
      void setBufferDimensions(const mk::Space::Vec2& bufferDimensions)
      {
        width = bufferDimensions.x;
        height = bufferDimensions.y;
      }
      /**
       * @brief Sets the title of the window.
       * @param title The new title of the window.
       */
      void setTitle(const std::string& title)
      {
        this->title = title;
        glfwSetWindowTitle(glfwInstance, title.c_str());
      }
      /**
       * @brief Sets the clear color of the window.
       * @param clearColor The new clear color of the window.
       */
      void setClearColor(const mk::Color::RGBA& clearColor)
      {
        this->clearColor = clearColor;
        glClearColor(
          clearColor.red,
          clearColor.green,
          clearColor.blue,
          clearColor.alpha
        );
      }
      /**
       * @brief Sets the maximized state of the window.
       * @param isMaximized The new maximized state of the window.
       */
      void setIsMaximized(const bool isMaximized)
      { this->isMaximized = isMaximized; }

      /**
       * @brief Checks if the window is open.
       * @return True if the window is open, false otherwise.
       */
      bool isOpen() const
      { return !glfwWindowShouldClose(this->glfwInstance); };

      /**
       * @brief Checks if a specific key is currently pressed.
       * @param key The key to check.
       * @return True if the key is pressed, false otherwise.
       */
      bool isKeyPressed(const mk::Input::Key& key) const
      { return glfwGetKey(this->glfwInstance, key) == GLFW_PRESS; }

      /**
       * @brief Adds a renderer to the list of renderers.
       * @param renderer The renderer to add.
       */
      void addRenderer(const mk::Render::Renderer& renderer);
      /**
       * @brief Removes a renderer from the list of renderers.
       * @param renderer The renderer to remove.
       */
      void removeRenderer(const mk::Render::Renderer& renderer);

      /**
       * @brief Maximizes the window.
       */
      void maximize();
      /**
       * @brief Restores the window to its normal size from a maximized state.
       */
      void unmaximize();

      /**
       * @brief Updates the window.
       */
      void update();
      /**
       * @brief Clears the contents of the window.
       */
      void clear();
      /**
       * @brief Displays the contents of the window.
       */
      void display();

    private:
      unsigned int width  {800u};
      unsigned int height {600u};
      std::string  title  {"MK Window"};

      GLFWwindow*     glfwInstance {nullptr};
      mk::Color::RGBA clearColor   {mk::Color::Black};

      float deltaTime {0.f};
      float lastTime  {static_cast<float>(glfwGetTime())};

      float        cachedX      {0.f};
      float        cachedY      {0.f};
      unsigned int cachedWidth  {0u};
      unsigned int cachedHeight {0u};
      bool         isMaximized  {false};

      std::vector<mk::Render::Renderer*> renderers;

      /**
       * @brief Initializes the window.
       * This function creates the GLFW window instance.
       */
      void _initialize();
      /**
       * @brief Updates the time taken to render the last frame.
       * This function calculates and updates the delta time.
       */
      void _updateDeltaTime();
  };
}

#endif // MK_WINDOW_HPP
