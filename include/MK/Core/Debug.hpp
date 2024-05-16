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
    /**
     * @brief Prints the elements of a 4x4 matrix.
     * @param mat The 4x4 matrix to print.
     */
    inline void printMatrix(const mk::Space::Mat4& mat)
    {
      for (int y = 0; y < 4; y++)
      {
        for (int x = 0; x < 4; x++)
        {
          std::cout << mat[y][x] << ' ';
        }
        std::cout << '\n';
      }
    }
  }
}

#endif // MK_DEBUG_HPP
