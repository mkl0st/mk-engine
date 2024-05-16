#ifndef MK_RENDER_HPP
#define MK_RENDER_HPP

#include "Objects.hpp"
#include "Shapes.hpp"

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
        Renderer(mk::Graphics::Shader& shader)
        : shader(shader)
        {}

        /**
         * @brief Renders a shape using the specified shader.
         * @param shape The shape to be rendered.
         */
        void render(const mk::Shapes::Shape& shape);

      private:
        mk::Graphics::Shader& shader;
    };
  }
}

#endif // MK_RENDER_HPP
