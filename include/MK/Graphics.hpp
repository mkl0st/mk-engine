#ifndef MK_GRAPHICS_HPP
#define MK_GRAPHICS_HPP

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <array>

#include "Core/Constants.hpp"
#include "Core/Setup.hpp"
#include "Core/File.hpp"
#include "Graphics/Color.hpp"
#include "Graphics/Objects.hpp"
#include "Graphics/Window.hpp"
#include "Graphics/Shapes.hpp"

namespace mk
{
  /**
   * @brief Namespace for graphics-related functionality of the MK Engine.
   * @namespace Graphics
   */
  namespace Graphics
  {
    /**
     * @brief Namespace for graphics-related functionality of the MK Engine.
     */
    inline void usePointMode()
    { glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); }
    /**
     * @brief Sets the OpenGL polygon mode to line mode.
     */
    inline void useLineMode()
    { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
    /**
     * @brief Sets the OpenGL polygon mode to fill mode.
     */
    inline void useFillMode()
    { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
  }
}

#endif // MK_GRAPHICS_HPP
