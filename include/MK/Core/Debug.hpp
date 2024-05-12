#ifndef MK_DEBUG_HPP
#define MK_DEBUG_HPP

#include <iostream>

#include "Space.hpp"

namespace mk
{
  /**
   * @brief Namespace for debug-related functionality of the MK Engine.
   */
  namespace Debug
  {
    /**
     * @brief Prints the components of a 2D vector.
     * @param vec The 2D vector to print.
     */
    inline void printVector(const mk::Space::Vec2& vec)
    {
      std::cout << "X: " << vec.x << "; Y: " << vec.y << '\n';
    }
    /**
     * @brief Prints the components of a 3D vector.
     * @param vec The 3D vector to print.
     */
    inline void printVector(const mk::Space::Vec3& vec)
    {
      std::cout << "X: " << vec.x << "; Y: " << vec.y << "; Z: " << vec.z << '\n';
    }
  }
}

#endif // MK_DEBUG_HPP
