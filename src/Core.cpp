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

mk::Space::Mat4 mk::Space::translate(mk::Space::Mat4 mat, const mk::Space::Vec2& vec)
{
  mat[3][0] = vec.x;
  mat[3][1] = vec.y;
  return mat;
}

mk::Space::Mat4 mk::Space::translate(mk::Space::Mat4 mat, const mk::Space::Vec3& vec)
{
  mat[3][0] = vec.x;
  mat[3][1] = vec.y;
  mat[3][2] = vec.z;
  return mat;
}

mk::Space::Mat4 mk::Space::scale(mk::Space::Mat4 mat, const mk::Space::Vec2& vec)
{
  mat[0][0] *= vec.x;
  mat[1][1] *= vec.y;
  return mat;
}

mk::Space::Mat4 mk::Space::scale(mk::Space::Mat4 mat, const mk::Space::Vec3& vec)
{
  mat[0][0] *= vec.x;
  mat[1][1] *= vec.y;
  mat[2][2] *= vec.z;
  return mat;
}

mk::Space::Mat4 mk::Space::rotate(mk::Space::Mat4 mat, const mk::Space::Vec3& vec, const float angle)
{
  mk::Space::Vec3 normalizedAxes = mk::Space::normalize(vec);
  mk::Space::Mat4 result {mat};

  const float cosTheta = std::cos(mk::Space::radians(angle));
  const float sinTheta = std::sin(mk::Space::radians(angle));
  const float oneMinusCosTheta = 1.f - cosTheta;

  result[0][0] = cosTheta + normalizedAxes.x * normalizedAxes.x * oneMinusCosTheta;
  result[0][1] = normalizedAxes.x * normalizedAxes.y * oneMinusCosTheta - normalizedAxes.z * sinTheta;
  result[0][2] = normalizedAxes.x * normalizedAxes.z * oneMinusCosTheta + normalizedAxes.y * sinTheta;
  result[1][0] = normalizedAxes.y * normalizedAxes.x * oneMinusCosTheta + normalizedAxes.z * sinTheta;
  result[1][1] = cosTheta + normalizedAxes.y * normalizedAxes.y * oneMinusCosTheta;
  result[1][2] = normalizedAxes.y * normalizedAxes.z * oneMinusCosTheta - normalizedAxes.x * sinTheta;
  result[2][0] = normalizedAxes.z * normalizedAxes.x * oneMinusCosTheta - normalizedAxes.y * sinTheta;
  result[2][1] = normalizedAxes.z * normalizedAxes.y * oneMinusCosTheta + normalizedAxes.x * sinTheta;
  result[2][2] = cosTheta + normalizedAxes.z * normalizedAxes.z * oneMinusCosTheta;

  return result * mat;
}

mk::Space::Mat4 mk::Space::ortho(const float left, const float right, const float top, const float bottom, const float zNear, const float zFar)
{
  mk::Space::Mat4 result {1.f};

  result[0][0] = 2.f / (right - left);
  result[1][1] = 2.f / (top - bottom);
  result[2][2] = 2.f / (zFar - zNear);
  result[3][0] = -(right + left) / (right - left);
  result[3][1] = -(top + bottom) / (top - bottom);
  result[3][2] = -(zFar + zNear) / (zFar - zNear);

  return result;
}
