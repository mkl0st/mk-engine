#ifndef MK_GRAPHICS_HPP
#define MK_GRAPHICS_HPP

#include <GL/glew.h>
#include <iostream>
#include <string>

#include "Core/Constants.hpp"
#include "Core/File.hpp"
#include "Graphics/Color.hpp"

namespace mk
{
  /**
   * @brief Namespace for graphics-related functionality of the MK Engine.
   * @namespace Graphics
   */
  namespace Graphics
  {
    /**
     * @brief A class representing a shader program in OpenGL.
     */
    class Shader
    {
      public:
        /**
         * @brief Constructs a Shader object from vertex and fragment shader files.
         * @param vertexPath   The file path to the vertex shader source code.
         * @param fragmentPath The file path to the fragment shader source code.
         */
        Shader(const std::string& vertexPath, const std::string& fragmentPath);

        /**
         * @brief Activates the shader program.
         */
        void Use()
        { glUseProgram(this->ID); }
        /**
         * @brief Deletes the shader program.
         */
        void Delete()
        { glDeleteProgram(this->ID); }

      private:
        GLuint ID {0};
    };
  }
}

#endif // MK_GRAPHICS_HPP
