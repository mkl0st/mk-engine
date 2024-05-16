#ifndef MK_CAMERA_HPP
#define MK_CAMERA_HPP

#include <MK/Core/Space.hpp>

#include "Objects.hpp"

namespace mk
{
  /**
   * @brief A class representing a camera.
   */
  class Camera
  {
    public:
      /**
       * @brief Constructs a Camera object with the specified buffer dimensions, near clipping plane, and far clipping plane.
       * @param bufferDimensions The dimensions of the camera buffer.
       * @param zNear The distance to the near clipping plane.
       * @param zFar The distance to the far clipping plane.
       */
      Camera(const mk::Space::Vec2& bufferDimensions, const float zNear, const float zFar)
      : bufferDimensions(bufferDimensions), zNear(zNear), zFar(zFar)
      {}

      /**
       * @brief Gets the buffer dimensions of the camera.
       * @return The buffer dimensions of the camera.
       */
      mk::Space::Vec2 getBufferDimensions() const
      { return bufferDimensions; }
      /**
       * @brief Gets the distance to the near clipping plane.
       * @return The distance to the near clipping plane.
       */
      float getZNear() const
      { return zNear; }
      /**
       * @brief Gets the distance to the far clipping plane.
       * @return The distance to the far clipping plane.
       */
      float getZFar() const
      { return zFar; }

      /**
       * @brief Sets the buffer dimensions of the camera.
       * @param bufferDimensions The new buffer dimensions of the camera.
       */
      void setBufferDimensions(const mk::Space::Vec2& bufferDimensions)
      { this->bufferDimensions = bufferDimensions; }
      /**
       * @brief Sets the distance to the near clipping plane.
       * @param zNear The new distance to the near clipping plane.
       */
      void setZNear(const float zNear)
      { this->zNear = zNear; }
      /**
       * @brief Sets the distance to the far clipping plane.
       * @param zFar The new distance to the far clipping plane.
       */
      void setZFar(const float zFar)
      { this->zFar = zFar; }

      /**
       * @brief Applies the camera matrix to a shader.
       * @param shader The shader to which the camera matrix will be applied.
       */
      void applyMatrix(const mk::Graphics::Shader& shader)
      { shader.SetMat4("cameraMatrix", matrix); }

    private:
      mk::Space::Vec2 bufferDimensions {0.f};
      float zNear {0.f};
      float zFar {0.f};

      mk::Space::Mat4 matrix {1.f};
  };
}

#endif // MK_CAMERA_HPP
