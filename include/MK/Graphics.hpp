#ifndef MK_GRAPHICS_HPP
#define MK_GRAPHICS_HPP

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <array>

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

    /**
     * @brief A class representing a Vertex Buffer Object (VBO) in OpenGL.
     */
    class VBO
    {
      public:
        /**
         * @brief Constructs a VBO object with the specified vertex data.
         * @tparam size The size of the vertex data array.
         * @param vertices The array containing the vertex data.
         */
        template<std::size_t size>
        VBO(const std::array<GLfloat, size>& vertices)
        {
          glGenBuffers(1, &this->ID);
          glBindBuffer(GL_ARRAY_BUFFER, this->ID);
          glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
          glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        /**
         * @brief Binds the VBO.
         */
        void Bind()
        { glBindBuffer(GL_ARRAY_BUFFER, this->ID); }
        /**
         * @brief Unbinds the VBO.
         */
        void Unbind()
        { glBindBuffer(GL_ARRAY_BUFFER, 0); }
        /**
         * @brief Deletes the VBO.
         */
        void Delete()
        { glDeleteBuffers(1, &this->ID); }

      private:
        GLuint ID {0};
    };

    /**
     * @brief A class representing a Element Buffer Object (EBO) in OpenGL.
     */
    class EBO
    {
      public:
        /**
         * @brief Constructs a EBO object with the specified index data.
         * @tparam size The size of the index data array.
         * @param indices The array containing the index data.
         */
        template<std::size_t size>
        EBO(const std::array<GLuint, size>& indices)
        {
          glGenBuffers(1, &this->ID);
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
          glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLfloat), indices.data(), GL_STATIC_DRAW);
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        /**
         * @brief Binds the EBO.
         */
        void Bind()
        { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID); }
        /**
         * @brief Unbinds the EBO.
         */
        void Unbind()
        { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
        /**
         * @brief Deletes the EBO.
         */
        void Delete()
        { glDeleteBuffers(1, &this->ID); }

      private:
        GLuint ID {0};
    };
  }
}

#endif // MK_GRAPHICS_HPP
