#ifndef MK_SPACE_HPP
#define MK_SPACE_HPP

#include <cmath>

namespace mk
{
  /**
   * @brief Namespace for space-related functionality of the MK Engine.
   */
  namespace Space
  {
    /**
     * @brief Constant value for pi.
     */
    constexpr float PI = 3.141593f;

    /**
     * @brief Converts radians to degrees.
     * @param radians The angle in radians.
     * @return The angle in degrees.
     */
    inline float degrees(const float radians)
    { return radians * 180.0f / mk::Space::PI; }
    /**
     * @brief Converts degrees to radians.
     * @param degrees The angle in degrees.
     * @return The angle in radians.
     */
    inline float radians(const float degrees)
    { return degrees * mk::Space::PI / 180.0f; }

    /**
     * @brief A class representing a 2D vector.
     */
    class Vec2
    {
      public:
        /**
         * @brief Default constructor.
         * Initializes the vector to (0, 0).
         */
        Vec2()
        {}
        /**
         * @brief Constructor with a scalar value.
         * Initializes the vector to (scalar, scalar).
         * @param scalar The scalar value to initialize both components.
         */
        Vec2(const float scalar)
        : x(scalar), y(scalar)
        {}
        /**
         * @brief Constructor with specified x and y values.
         * @param x The x-component of the vector.
         * @param y The y-component of the vector.
         */
        Vec2(const float x, const float y)
        : x(x), y(y)
        {}

        /**
         * @brief Overloaded addition operator.
         * Adds two vectors component-wise.
         * @param vec The vector to add.
         * @return The result of the addition operation.
         */
        mk::Space::Vec2 operator+(const mk::Space::Vec2& vec) const
        {
          return
          {
            this->x + vec.x,
            this->y + vec.y,
          };
        }
        /**
         * @brief Overloaded subtraction operator.
         * Subtracts two vectors component-wise.
         * @param vec The vector to subtract.
         * @return The result of the subtraction operation.
         */
        mk::Space::Vec2 operator-(const mk::Space::Vec2& vec) const
        {
          return
          {
            this->x - vec.x,
            this->y - vec.y,
          };
        }
        /**
         * @brief Overloaded negation operator.
         * Negates the vector components.
         * @return The negated vector.
         */
        mk::Space::Vec2 operator-() const
        { return {-this->x, -this->y}; }
        /**
         * @brief Overloaded multiplication operator.
         * Multiplies the vector by a scalar value.
         * @tparam T The type of the scalar value.
         * @param scalar The scalar value to multiply with.
         * @return The result of the multiplication operation.
         */
        template<typename T>
        mk::Space::Vec2 operator*(const T scalar) const
        {
          return
          {
            this->x * scalar,
            this->y * scalar,
          };
        };
        /**
         * @brief Overloaded division operator.
         * Divides each component of the vector by a scalar value.
         * @tparam T The type of the scalar value.
         * @param scalar The scalar value to divide each component by.
         * @return The result of the division operation.
         */
        template<typename T>
        mk::Space::Vec2 operator/(const T scalar) const
        {
          return
          {
            this->x / scalar,
            this->y / scalar,
          };
        };
        /**
         * @brief Overloaded friend multiplication operator.
         * Multiplies a scalar value with the vector.
         * @tparam T The type of the scalar value.
         * @param scalar The scalar value to multiply with.
         * @param vec The vector to multiply with the scalar.
         * @return The result of the multiplication operation.
         */
        template<typename T>
        friend mk::Space::Vec2 operator*(const T scalar, const mk::Space::Vec2& vec)
        {
          return
          {
            vec.x * scalar,
            vec.y * scalar,
          };
        };
        /**
         * @brief Overloaded friend division operator.
         * Divides each component of a vector by a scalar value.
         * @tparam T The type of the scalar value.
         * @param scalar The scalar value to divide each component by.
         * @param vec The vector whose components will be divided.
         * @return The result of the division operation.
         */
        template<typename T>
        friend mk::Space::Vec2 operator/(const T scalar, const mk::Space::Vec2& vec)
        {
          return
          {
            vec.x / scalar,
            vec.y / scalar,
          };
        };
        /**
         * @brief Compound addition assignment operator.
         * Adds another vector to this vector.
         * @param vec The vector to add.
         * @return Reference to the updated vector.
         */
        mk::Space::Vec2& operator+=(const mk::Space::Vec2& vec)
        {
          this->x += vec.x;
          this->y += vec.y;
          return *this;
        }
        /**
         * @brief Compound subtraction assignment operator.
         * Subtracts another vector from this vector.
         * @param vec The vector to subtract.
         * @return Reference to the updated vector.
         */
        mk::Space::Vec2& operator-=(const mk::Space::Vec2& vec)
        {
          this->x -= vec.x;
          this->y -= vec.y;
          return *this;
        }
        /**
         * @brief Compound multiplication assignment operator.
         * Multiplies the vector by a scalar value.
         * @tparam T The type of the scalar value.
         * @param scalar The scalar value to multiply with.
         * @return Reference to the updated vector.
         */
        template<typename T>
        mk::Space::Vec2& operator*=(const T scalar)
        {
          this->x *= scalar;
          this->y *= scalar;
          return *this;
        }
        /**
         * @brief Compound division assignment operator.
         * Divides each component of the vector by a scalar value.
         * @tparam T The type of the scalar value.
         * @param scalar The scalar value to divide each component by.
         * @return Reference to the updated vector.
         */
        template<typename T>
        mk::Space::Vec2& operator/=(const T scalar)
        {
          this->x /= scalar;
          this->y /= scalar;
          return *this;
        }

        float x {0.f};
        float y {0.f};
    };

    /**
     * @brief A class representing a 3D vector.
     */
    class Vec3
    {
      public:
        /**
         * @brief Default constructor.
         * Initializes the vector to (0, 0, 0).
         */
        Vec3()
        {}
        /**
         * @brief Constructor with a scalar value.
         * Initializes the vector to (scalar, scalar, scalar).
         * @param scalar The scalar value to initialize all components.
         */
        Vec3(const float scalar)
        : x(scalar), y(scalar), z(scalar)
        {}
        /**
         * @brief Constructor with specified x, y, and z values.
         * @param x The x-component of the vector.
         * @param y The y-component of the vector.
         * @param z The z-component of the vector.
         */
        Vec3(const float x, const float y, const float z)
        : x(x), y(y), z(z)
        {}

        /**
         * @brief Overloaded addition operator.
         * Adds two vectors component-wise.
         * @param vec The vector to add.
         * @return The result of the addition operation.
         */
        mk::Space::Vec3 operator+(const mk::Space::Vec3& vec) const
        {
          return
          {
            this->x + vec.x,
            this->y + vec.y,
            this->z + vec.z,
          };
        }
        /**
         * @brief Overloaded subtraction operator.
         * Subtracts two vectors component-wise.
         * @param vec The vector to subtract.
         * @return The result of the subtraction operation.
         */
        mk::Space::Vec3 operator-(const mk::Space::Vec3& vec) const
        {
          return
          {
            this->x - vec.x,
            this->y - vec.y,
            this->z - vec.z,
          };
        }
        /**
         * @brief Overloaded negation operator.
         * Negates the vector components.
         * @return The negated vector.
         */
        mk::Space::Vec3 operator-() const
        { return {-this->x, -this->y, -this->z}; }
        /**
         * @brief Overloaded multiplication operator.
         * Multiplies the vector by a scalar value.
         * @tparam T The type of the scalar value.
         * @param scalar The scalar value to multiply with.
         * @return The result of the multiplication operation.
         */
        template<typename T>
        mk::Space::Vec3 operator*(const T scalar) const
        {
          return
          {
            this->x * scalar,
            this->y * scalar,
            this->z * scalar,
          };
        };
        /**
         * @brief Overloaded division operator.
         * Divides each component of the vector by a scalar value.
         * @tparam T The type of the scalar value.
         * @param scalar The scalar value to divide each component by.
         * @return The result of the division operation.
         */
        template<typename T>
        mk::Space::Vec3 operator/(const T scalar) const
        {
          return
          {
            this->x / scalar,
            this->y / scalar,
            this->z / scalar,
          };
        };
        /**
         * @brief Overloaded friend multiplication operator.
         * Multiplies a scalar value with the vector.
         * @tparam T The type of the scalar value.
         * @param scalar The scalar value to multiply with.
         * @param vec The vector to multiply with the scalar.
         * @return The result of the multiplication operation.
         */
        template<typename T>
        friend mk::Space::Vec3 operator*(const T scalar, const mk::Space::Vec3& vec)
        {
          return
          {
            vec.x * scalar,
            vec.y * scalar,
            vec.z * scalar,
          };
        };
        /**
         * @brief Overloaded friend division operator.
         * Divides each component of a vector by a scalar value.
         * @tparam T The type of the scalar value.
         * @param scalar The scalar value to divide each component by.
         * @param vec The vector whose components will be divided.
         * @return The result of the division operation.
         */
        template<typename T>
        friend mk::Space::Vec3 operator/(const T scalar, const mk::Space::Vec3& vec)
        {
          return
          {
            vec.x / scalar,
            vec.y / scalar,
            vec.z / scalar,
          };
        };
        /**
         * @brief Compound addition assignment operator.
         * Adds another vector to this vector.
         * @param vec The vector to add.
         * @return Reference to the updated vector.
         */
        mk::Space::Vec3& operator+=(const mk::Space::Vec3& vec)
        {
          this->x += vec.x;
          this->y += vec.y;
          this->z += vec.z;
          return *this;
        }
        /**
         * @brief Compound subtraction assignment operator.
         * Subtracts another vector from this vector.
         * @param vec The vector to subtract.
         * @return Reference to the updated vector.
         */
        mk::Space::Vec3& operator-=(const mk::Space::Vec3& vec)
        {
          this->x -= vec.x;
          this->y -= vec.y;
          this->z -= vec.z;
          return *this;
        }
        /**
         * @brief Compound multiplication assignment operator.
         * Multiplies the vector by a scalar value.
         * @tparam T The type of the scalar value.
         * @param scalar The scalar value to multiply with.
         * @return Reference to the updated vector.
         */
        template<typename T>
        mk::Space::Vec3& operator*=(const T scalar)
        {
          this->x *= scalar;
          this->y *= scalar;
          this->z *= scalar;
          return *this;
        }
        /**
         * @brief Compound division assignment operator.
         * Divides each component of the vector by a scalar value.
         * @tparam T The type of the scalar value.
         * @param scalar The scalar value to divide each component by.
         * @return Reference to the updated vector.
         */
        template<typename T>
        mk::Space::Vec3& operator/=(const T scalar)
        {
          this->x /= scalar;
          this->y /= scalar;
          this->z /= scalar;
          return *this;
        }

        float x {0.f};
        float y {0.f};
        float z {0.f};
    };

    /**
     * @brief Calculates the length of a 2D vector.
     * @param vec The 2D vector.
     * @return The length of the vector.
     */
    inline float length(const mk::Space::Vec2& vec)
    { return std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2)); }
    /**
     * @brief Calculates the length of a 3D vector.
     * @param vec The 3D vector.
     * @return The length of the vector.
     */
    inline float length(const mk::Space::Vec3& vec)
    { return std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2) + std::pow(vec.z, 2)); }
    /**
     * @brief Normalizes a 2D vector.
     * @param vec The 2D vector to normalize.
     * @return The normalized vector.
     */
    inline mk::Space::Vec2 normalize(const mk::Space::Vec2& vec)
    {
      const float length = mk::Space::length(vec);
      return length > 0.f
        ? vec / length
        : mk::Space::Vec2(0.f);
    }
    /**
     * @brief Normalizes a 3D vector.
     * @param vec The 3D vector to normalize.
     * @return The normalized vector.
     */
    inline mk::Space::Vec3 normalize(const mk::Space::Vec3& vec)
    {
      const float length = mk::Space::length(vec);
      return length > 0.f
        ? vec / length
        : mk::Space::Vec3(0.f);
    }
    /**
     * @brief Calculates the dot product of two 2D vectors.
     * @param vecOne The first 2D vector.
     * @param vecTwo The second 2D vector.
     * @return The dot product of the two vectors.
     */
    inline float dot(const mk::Space::Vec2& vecOne, const mk::Space::Vec2& vecTwo)
    { return vecOne.x * vecTwo.x + vecOne.y * vecTwo.y; }
    /**
     * @brief Calculates the dot product of two 3D vectors.
     * @param vecOne The first 3D vector.
     * @param vecTwo The second 3D vector.
     * @return The dot product of the two vectors.
     */
    inline float dot(const mk::Space::Vec3& vecOne, const mk::Space::Vec3& vecTwo)
    { return vecOne.x * vecTwo.x + vecOne.y * vecTwo.y + vecOne.z * vecTwo.z; }
    /**
     * @brief Calculates the cross product of two 3D vectors.
     * @param vecOne The first 3D vector.
     * @param vecTwo The second 3D vector.
     * @return The cross product of the two vectors.
     */
    inline mk::Space::Vec3 cross(const mk::Space::Vec3& vecOne, const mk::Space::Vec3& vecTwo)
    {
      return
      {
        vecOne.y * vecTwo.z - vecOne.z * vecTwo.y,
        vecOne.z * vecTwo.x - vecOne.x * vecTwo.z,
        vecOne.x * vecTwo.y - vecOne.y * vecTwo.x,
      };
    };

    /**
     * @brief A class representing a 4x4 matrix.
     */
    class Mat4
    {
      public:
        /**
         * @brief Default constructor.
         * Initializes the matrix to be a 4x4 matrix with all elements set to 0.
         */
        Mat4()
        {
          for (int y = 0; y < 4; y++)
            for (int x = 0; x < 4; x++)
              elements[y][x] = 0.f;
        }
        /**
         * @brief Constructor with a diagonal value.
         * Initializes the matrix to be a 4x4 matrix with diagonal elements set to the specified value
         * and all other elements set to 0.
         * @param diagonalValue The value to set the diagonal elements to.
         */
        Mat4(const float diagonalValue)
        {
          for (int y = 0; y < 4; y++)
            for (int x = 0; x < 4; x++)
              elements[y][x] = x == y ? diagonalValue : 0.f;
        }

        /**
         * @brief Overloaded subscript operator.
         * Allows access to the elements of the matrix.
         * @param index The row index.
         * @return A pointer to the array of elements in the specified row.
         */
        float* operator[](int index)
        { return elements[index]; }
        /**
         * @brief Overloaded const subscript operator.
         * Allows read-only access to the elements of the matrix.
         * @param index The row index.
         * @return A const pointer to the array of elements in the specified row.
         */
        const float* operator[](int index) const
        { return elements[index]; }
        /**
         * @brief Overloaded multiplication operator for matrix multiplication.
         * Multiplies this matrix by another matrix.
         * @param other The matrix to multiply with.
         * @return The resulting matrix after multiplication.
         */
        mk::Space::Mat4 operator*(const mk::Space::Mat4& mat)
        {
          mk::Space::Mat4 result;
          for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
              result[i][j] = 0.f;
              for (int k = 0; k < 4; k++)
                result[i][j] += elements[i][k] * mat[k][j];
            }
          return result;
        }

      private:
        float elements[4][4];
    };

    /**
     * @brief Retrieves a pointer to the raw data of a 4x4 matrix.
     * @param mat The 4x4 matrix.
     * @return A const pointer to the raw data of the matrix.
     */
    inline const float* valuePointer(const mk::Space::Mat4& mat)
    { return &mat[0][0]; }
    /**
     * @brief Translates a 4x4 matrix by a 2D vector.
     * @param mat The original 4x4 matrix.
     * @param vec The translation vector.
     * @return The translated 4x4 matrix.
     */
    mk::Space::Mat4 translate(mk::Space::Mat4 mat, const mk::Space::Vec2& vec);
    /**
     * @brief Translates a 4x4 matrix by a 3D vector.
     * @param mat The original 4x4 matrix.
     * @param vec The translation vector.
     * @return The translated 4x4 matrix.
     */
    mk::Space::Mat4 translate(mk::Space::Mat4 mat, const mk::Space::Vec3& vec);
    /**
     * @brief Scales a 4x4 matrix by a 2D vector.
     * @param mat The original 4x4 matrix.
     * @param vec The scale vector.
     * @return The scaled 4x4 matrix.
     */
    mk::Space::Mat4 scale(mk::Space::Mat4 mat, const mk::Space::Vec2& vec);
    /**
     * @brief Scales a 4x4 matrix by a 3D vector.
     * @param mat The original 4x4 matrix.
     * @param vec The scale vector.
     * @return The scaled 4x4 matrix.
     */
    mk::Space::Mat4 scale(mk::Space::Mat4 mat, const mk::Space::Vec3& vec);
    /**
     * @brief Rotates a 4x4 matrix by a given angle around a 3D vector.
     * @param mat The original 4x4 matrix.
     * @param vec The axis vector around which the rotation occurs.
     * @param angle The angle of rotation in degrees.
     * @return The rotated 4x4 matrix.
     */
    mk::Space::Mat4 rotate(mk::Space::Mat4 mat, const mk::Space::Vec3& vec, const float angle);
    /**
     * @brief Creates an orthographic projection matrix.
     * @param left The coordinate of the left vertical clipping plane.
     * @param right The coordinate of the right vertical clipping plane.
     * @param top The coordinate of the top horizontal clipping plane.
     * @param bottom The coordinate of the bottom horizontal clipping plane.
     * @param zNear The distance to the near clipping plane.
     * @param zFar The distance to the far clipping plane.
     * @return The orthographic projection matrix.
     */
    mk::Space::Mat4 ortho(const float left, const float right, const float top, const float bottom, const float zNear, const float zFar);
  }
}

#endif // MK_SPACE_HPP
