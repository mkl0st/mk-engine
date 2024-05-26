#ifndef MK_IMAGE_HPP
#define MK_IMAGE_HPP

#include <GL/glew.h>
#include <libpng16/png.h>
#include <stdio.h>
#include <string>

namespace mk
{
  /**
   * @brief Namespace for image-related functionality of the MK Engine.
   * @namespace Image
   */
  namespace Image
  {
    /**
     * @brief Loads an image from a PNG file.
     * @param pngPath The file path to the PNG image.
     * @param oData Output parameter that will point to the image data.
     * @param oWidth Output parameter that will hold the width of the image.
     * @param oHeight Output parameter that will hold the height of the image.
     * @param oHasAlpha Output parameter that will indicate whether the image has an alpha channel.
     * @return True if the image was loaded successfully, false otherwise.
     */
    bool loadFromPNG(const std::string& pngPath, GLubyte** oData, GLuint& oWidth, GLuint& oHeight, bool& oHasAlpha);
  }
}

#endif // MK_IMAGE_HPP
