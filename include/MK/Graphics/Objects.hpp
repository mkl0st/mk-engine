#ifndef MK_OBJECTS_HPP
#define MK_OBJECTS_HPP

#include <GL/glew.h>
#include <string>

namespace mk
{
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
        void Use() const
        { glUseProgram(this->ID); }
        /**
         * @brief Deletes the shader program.
         */
        void Delete() const
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
        void Bind() const
        { glBindBuffer(GL_ARRAY_BUFFER, this->ID); }
        /**
         * @brief Unbinds the VBO.
         */
        void Unbind() const
        { glBindBuffer(GL_ARRAY_BUFFER, 0); }
        /**
         * @brief Deletes the VBO.
         */
        void Delete() const
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
        void Bind() const
        { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID); }
        /**
         * @brief Unbinds the EBO.
         */
        void Unbind() const
        { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
        /**
         * @brief Deletes the EBO.
         */
        void Delete() const
        { glDeleteBuffers(1, &this->ID); }

      private:
        GLuint ID {0};
    };

    /**
     * @brief A class representing a Vertex Array Object (VAO) in OpenGL.
     */
    class VAO
    {
      public:
        /**
         * @brief Constructs a VAO object.
         */
        VAO()
        { glGenVertexArrays(1, &this->ID); };

        /**
         * @brief Binds the VAO.
         */
        void Bind() const
        { glBindVertexArray(this->ID); }
        /**
         * @brief Unbinds the VAO.
         */
        void Unbind() const
        { glBindVertexArray(0); }
        /**
         * @brief Deletes the VAO.
         */
        void Delete() const
        { glDeleteVertexArrays(1, &this->ID); }
        /**
         * @brief Links a VBO to this VAO.
         * @param VBO     The VBO to link.
         * @param layout  The layout location of the vertex attribute.
         * @param size    The number of components per vertex attribute.
         * @param type    The data type of each component in the vertex attribute.
         * @param stride  The byte offset between consecutive generic vertex attributes.
         * @param offset  The offset of the first component of the first vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target.
         */
        void LinkAttrib(const mk::Graphics::VBO& VBO, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, const void* offset) const;

      private:
        GLuint ID {0};
    };
  };
}

#endif //  MK_OBJECTS_HPP
