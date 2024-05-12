#ifndef MK_SETUP_HPP
#define MK_SETUP_HPP

namespace mk
{
  namespace Core
  {
    /**
     * Initialize GLFW (Graphics Library Framework).
     * @return True if GLFW was initialized successfully, false otherwise.
     */
    bool initializeGLFW();
    /**
     * Initialize GLEW (OpenGL Extension Wrangler Library).
     * @return True if GLEW was initialized successfully, false otherwise.
     */
    bool initializeGLEW();

    /**
     * @brief Prints information about the MK Engine.
     */
    void printEngineInfo();
    /**
     * @brief Prints version information about the MK Engine dependencies.
     */
    void printVersionInfo();

    /**
     * @brief Terminates the MK Engine.
     */
    void terminate();
  }
}

#endif // MK_SETUP_HPP
