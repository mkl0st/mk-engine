#ifndef MK_RENDER_HPP
#define MK_RENDER_HPP

#include "Objects.hpp"
#include "Shapes.hpp"
#include "Camera.hpp"

namespace mk
{
  /**
   * @brief Namespace for render-related functionality of the MK Engine.
   * @namespace Render
   */
  namespace Render
  {
    /**
     * @brief A class responsible for rendering shapes using a specified shader.
     */
    class Renderer
    {
      public:
        /**
         * @brief Constructs a Renderer object with the specified shader.
         * @param shader The shader to be used for rendering.
         */
        Renderer(mk::Graphics::Shader& shader, mk::Camera& camera)
        : shader(shader), camera(camera)
        {}

        /**
         * @brief Retrieves the camera used by the renderer.
         * @return A reference to the camera.
         */
        mk::Camera& getCamera() const
        { return camera; }

        /**
         * @brief Uses the shader for rendering.
         * This function sets the current shader to be used for rendering,
         * updates the camera matrix, and applies the camera matrix to the shader.
         */
        void use();
        /**
         * @brief Renders a shape using the specified shader.
         * @param shape The shape to be rendered.
         */
        void render(const mk::Shapes::Shape& shape) const;

      private:
        mk::Graphics::Shader& shader;
        mk::Camera& camera;
    };
  }
}

#endif // MK_RENDER_HPP
