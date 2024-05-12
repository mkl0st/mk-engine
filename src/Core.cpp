#include <MK/Core.hpp>

bool mk::Core::initializeGLFW()
{
  bool success = glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mk::Constants::GL_MAJOR_VER);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mk::Constants::GL_MINOR_VER);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  return success;
}

bool mk::Core::initializeGLEW()
{
  GLenum glewErr = glewInit();
  if (glewErr != GLEW_OK)
  {
    std::cerr << "Failed to initialize GLEW!\n";
    std::cerr << "Error: " << glewGetErrorString(glewErr) << '\n';
    return false;
  }
  return true;
}

void mk::Core::printEngineInfo()
{
  std::cout << mk::Constants::ENGINE_NAME << " " << mk::Constants::ENGINE_VERSION << '\n';
  std::cout << "Created by " << mk::Constants::ENGINE_AUTHOR << '\n';
  std::cout << "Licensed under " << mk::Constants::ENGINE_LICENSE << '\n';
}

void mk::Core::printVersionInfo()
{
  std::cout << "OpenGL: " << glGetString(GL_VERSION) << '\n';
  std::cout << "GLEW:   " << glewGetString(GLEW_VERSION) << '\n';
  std::cout << "GLFW:   " << glfwGetVersionString() << '\n';
}

void mk::Core::terminate()
{
  glfwTerminate();
}

std::string mk::File::getContents(const std::string& path)
{
  std::ifstream file(path);
  if (!file.is_open())
  {
    std::cerr << "Failed to open file (" << path << ")!\n";
    return "";
  }
  std::ostringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}
