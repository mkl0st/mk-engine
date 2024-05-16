#ifndef MK_COLOR_HPP
#define MK_COLOR_HPP

#include <stdint.h>

#include <MK/Core/Space.hpp>

namespace mk
{
  /**
   * Namespace for color-related functionality of the MK Engine.
   * @namespace Color
   */
  namespace Color
  {
    /**
     * @brief Represents an RGBA color with floating-point precision.
     */
    struct RGBA
    {
      float red;
      float green;
      float blue;
      float alpha;

      /**
       * Constructor for RGBA color.
       *
       * @param red   The red component value (0-255).
       * @param green The green component value (0-255).
       * @param blue  The blue component value (0-255).
       * @param alpha The alpha (transparency) component value (0.0-1.0).
       */
      RGBA(
        const uint8_t red,
        const uint8_t green,
        const uint8_t blue,
        const float alpha
      ) : red(red / 255.f), green(green / 255.f), blue(blue / 255.f), alpha(alpha)
      {}

      /**
       * @brief Converts RGBA color to RGB vector.
       * @return A 3D vector representing the RGB components of the color.
       */
      mk::Space::Vec3 toRGBVec() const
      { return {red, green, blue}; }
    };

    /**
     * @brief  black color.
     */
    inline const mk::Color::RGBA Black {0, 0, 0, 1.f};
    /**
     * @brief Predefined white color.
     */
    inline const mk::Color::RGBA White {255, 255, 255, 1.f};
    /**
     * @brief Predefined red color.
     */
    inline const mk::Color::RGBA Red {255, 0, 0, 1.f};
    /**
     * @brief Predefined green color.
     */
    inline const mk::Color::RGBA Green {0, 255, 0, 1.f};
    /**
     * @brief Predefined blue color.
     */
    inline const mk::Color::RGBA Blue {0, 0, 255, 1.f};
    /**
     * @brief Predefined yellow color.
     */
    inline const mk::Color::RGBA Yellow {255, 255, 0, 1.f};
    /**
     * @brief Predefined magenta color.
     */
    inline const mk::Color::RGBA Magenta {255, 0, 255, 1.f};
    /**
     * @brief Predefined cyan color.
     */
    inline const mk::Color::RGBA Cyan {0, 255, 255, 1.f};
  }
}

#endif // MK_COLOR_HPP
