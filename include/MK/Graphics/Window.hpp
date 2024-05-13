#ifndef MK_WINDOW_HPP
#define MK_WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

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
       * @brief Gets the title of the window.
       * @return The title of the window.
       */
      std::string getTitle() const
      { return title; }

      /**
       * @brief Sets the title of the window.
       * @param title The new title of the window.
       */
      void setTitle(const std::string& title)
      { this->title = title; }

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
       * @brief Updates the window.
       */
      void update();
      /**
       * @brief Clears the contents of the window.
       */
      void clear();
      /**
       * @brief Draws a shape on the window.
       * @param shape The shape to be drawn.
       */
      void draw(const mk::Shapes::Shape& shape);
      /**
       * @brief Render the contents of the window.
       */
      void render();

    private:
      unsigned int width  {800u};
      unsigned int height {600u};
      std::string  title  {"MK Window"};

      GLFWwindow* glfwInstance {nullptr};

      /**
       * @brief Initializes the window.
       * This function creates the GLFW window instance.
       */
      void _initialize();
  };
}

#endif // MK_WINDOW_HPP
