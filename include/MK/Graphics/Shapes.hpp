#ifndef MK_SHAPES_HPP
#define MK_SHAPES_HPP

#include <MK/Core/Space.hpp>

#include "Objects.hpp"

namespace mk
{
  /**
   * @brief Namespace for geometric shapes used in the MK Engine.
   * @namespace Shapes
   */
  namespace Shapes
  {
    /**
     * @brief Represents a rectangular boundary.
     */
    typedef struct BoundRect
    {
      float x;
      float y;
      float width;
      float height;

      /**
       * @brief Constructs a BoundRect object with the specified parameters.
       * @param x The x-coordinate of the top-left corner of the rectangle.
       * @param y The y-coordinate of the top-left corner of the rectangle.
       * @param width The width of the rectangle.
       * @param height The height of the rectangle.
       */
      BoundRect(const float x, const float y, const float width, const float height)
      : x(x), y(y), width(width), height(height)
      {}
    } BoundRect;

    /**
     * @brief Base class for geometric shapes.
     */
    class Shape
    {
      public:
        /**
         * @brief Constructs a Shape object with a position and index count.
         * @param position The position of the shape.
         * @param indexCount The number of indices in the shape.
         */
        Shape(const mk::Space::Vec2& position, const unsigned int indexCount)
        : position(position), indexCount(indexCount)
        {}
        /**
         * @brief Virtual destructor.
         * Deletes associated vertex array, vertex buffer, and element buffer objects.
         */
        virtual ~Shape()
        {
          VAO->Delete();
          VBO->Delete();
          EBO->Delete();
        }

        /**
         * @brief Retrieves the position of the shape.
         * @return The position of the shape.
         */
        mk::Space::Vec2 getPosition() const
        { return position; }
        /**
         * @brief Retrieves the boundary rectangle of the shape.
         * @return The boundary rectangle of the shape.
         */
        virtual mk::Shapes::BoundRect getBounds() const = 0;
        /**
         * @brief Retrieves the number of indices in the shape.
         * @return The number of indices.
         */
        unsigned int getIndexCount() const
        { return indexCount; }
        /**
         * @brief Retrieves the vertex array object of the shape.
         * @return A pointer to the vertex array object.
         */
        const mk::Graphics::VAO* getVAO() const
        { return VAO; }
        /**
         * @brief Retrieves the vertex buffer object of the shape.
         * @return A pointer to the vertex buffer object.
         */
        const mk::Graphics::VBO* getVBO() const
        { return VBO; }
        /**
         * @brief Retrieves the element buffer object of the shape.
         * @return A pointer to the element buffer object.
         */
        const mk::Graphics::EBO* getEBO() const
        { return EBO; }

        /**
         * @brief Sets the position of the shape.
         * @param position The new position of the shape.
         */
        void setPosition(const mk::Space::Vec2& position)
        { this->position = position; }

        /**
         * @brief Moves the shape along the X-axis by the specified amount.
         * @param amount The amount by which to move the shape along the X-axis.
         */
        void moveX(const float amount)
        { position.x += amount; }
        /**
         * @brief Moves the shape along the Y-axis by the specified amount.
         * @param amount The amount by which to move the shape along the Y-axis.
         */
        void moveY(const float amount)
        { position.y += amount; }
        /**
         * @brief Moves the shape by the specified amount in both the X and Y axes.
         * @param amount The amount by which to move the shape in both axes.
         */
        void move(const mk::Space::Vec2& amount)
        { position += amount; }

      protected:
        mk::Space::Vec2 position {0.f};
        unsigned int indexCount {0};

        mk::Graphics::VAO* VAO {nullptr};
        mk::Graphics::VBO* VBO {nullptr};
        mk::Graphics::EBO* EBO {nullptr};
    };

    /**
     * @brief Class representing a rectangle shape.
     */
    class Rectangle : public mk::Shapes::Shape
    {
      public:
        /**
         * @brief Constructs a Rectangle object with a position, width, and height.
         * @param position The position of the rectangle.
         * @param width The width of the rectangle.
         * @param height The height of the rectangle.
         */
        Rectangle(const mk::Space::Vec2& position, const float width, const float height);

        /**
         * @brief Retrieves the boundary rectangle of the rectangle shape.
         * @return The boundary rectangle of the rectangle shape.
         */
        mk::Shapes::BoundRect getBounds() const override
        { return BoundRect(position.x, position.y, width, height); }
        /**
         * @brief Retrieves the width of the rectangle.
         * @return The width of the rectangle.
         */
        float getWidth() const
        { return width; }
        /**
         * @brief Retrieves the height of the rectangle.
         * @return The height of the rectangle.
         */
        float getHeight() const
        { return height; }

      private:
        float width {0.f};
        float height {0.f};
    };
  }
}

#endif // MK_SHAPES_HPP
