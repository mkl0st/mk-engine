#ifndef MK_CONSTANTS_HPP
#define MK_CONSTANTS_HPP

#include <string>

namespace mk
{
   /**
   * Namespace for constants used in the MK Engine.
   * @namespace Constants
   */
  namespace Constants
  {
    /**
     * @brief The name of the MK Engine.
     */
    const std::string ENGINE_NAME    {"MK Engine"};
    /**
     * @brief The version of the MK Engine.
     */
    const std::string ENGINE_VERSION {"0.1 InDev"};
    /**
     * @brief The author of the MK Engine.
     */
    const std::string ENGINE_AUTHOR  {"mkl0st"};
    /**
     * @brief The license under which the MK Engine is distributed.
     */
    const std::string ENGINE_LICENSE {"GNU GPLv3"};

    /**
     * @brief The major version of OpenGL supported by the MK Engine.
     */
    constexpr unsigned int GL_MAJOR_VER {3};
    /**
     * @brief The minor version of OpenGL supported by the MK Engine.
     */
    constexpr unsigned int GL_MINOR_VER {3};

    /**
     * @brief The size of the info log buffer used for OpenGL error messages.
     */
    constexpr unsigned int INFO_LOG_SIZE {512u};
  }
}

#endif // MK_CONSTANTS_HPP
