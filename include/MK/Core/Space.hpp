#ifndef MK_SPACE_HPP
#define MK_SPACE_HPP

namespace mk
{
  /**
   * @brief Namespace for space-related functionality of the MK Engine.
   */
  namespace Space
  {
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

        float x {0.f};
        float y {0.f};
        float z {0.f};
    };

  }
}

#endif // MK_SPACE_HPP
