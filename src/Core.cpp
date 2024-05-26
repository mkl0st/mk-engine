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

bool mk::Image::loadFromPNG(const std::string& pngPath, GLubyte** oData, GLuint& oWidth, GLuint& oHeight, bool& oHasAlpha)
{
  FILE* imageFile = fopen(pngPath.c_str(), "rb");
  if (!imageFile)
  {
    std::cerr << "Failed to open image (" << pngPath << ")!\n";
    return false;
  }

  png_structp pngPointer = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!pngPointer)
  {
    std::cerr << "Failed to create a PNG read struct!\n";
    fclose(imageFile);
    return false;
  }

  png_infop pngInfoPointer = png_create_info_struct(pngPointer);
  if (!pngInfoPointer)
  {
    std::cerr << "Failed to create a PNG info struct!\n";
    png_destroy_read_struct(&pngPointer, NULL, NULL);
    fclose(imageFile);
    return false;
  }

  if (setjmp(png_jmpbuf(pngPointer)))
  {
    png_destroy_read_struct(&pngPointer, NULL, NULL);
    fclose(imageFile);
    return false;
  }

  png_init_io(pngPointer, imageFile);
  png_read_info(pngPointer, pngInfoPointer);

  oWidth = png_get_image_width(pngPointer, pngInfoPointer);
  oHeight = png_get_image_height(pngPointer, pngInfoPointer);
  png_byte colorType = png_get_color_type(pngPointer, pngInfoPointer);
  png_byte bitDepth = png_get_bit_depth(pngPointer, pngInfoPointer);

  if (colorType == PNG_COLOR_TYPE_PALETTE)
  {
    png_set_palette_to_rgb(pngPointer);
  }
  else if (colorType ==  PNG_COLOR_TYPE_GRAY && bitDepth < 8)
  {
    png_set_expand_gray_1_2_4_to_8(pngPointer);
  }

  if (png_get_valid(pngPointer, pngInfoPointer, PNG_INFO_tRNS))
  {
    png_set_tRNS_to_alpha(pngPointer);
  }

  if (bitDepth == 16)
  {
    png_set_strip_16(pngPointer);
  }
  if (colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
  {
    png_set_gray_to_rgb(pngPointer);
  }

  png_read_update_info(pngPointer, pngInfoPointer);

  *oData = (GLubyte*)malloc(png_get_rowbytes(pngPointer, pngInfoPointer) * oHeight);
  if (!*oData)
  {
    std::cerr << "Failed to allocate memory for image data!\n";
    png_destroy_read_struct(&pngPointer, NULL, NULL);
    fclose(imageFile);
    return false;
  }

  png_bytep* rowPointers = (png_bytep*)malloc(sizeof(png_bytep) * oHeight);
  for (int y = 0; y < oHeight; y++)
  {
    rowPointers[y] = *oData + (png_get_rowbytes(pngPointer, pngInfoPointer) * y);
  }

  png_read_image(pngPointer, rowPointers);
  png_free(pngPointer, rowPointers);
  png_destroy_read_struct(&pngPointer, NULL, NULL);

  oHasAlpha = (colorType & PNG_COLOR_MASK_ALPHA) != 0;

  fclose(imageFile);
  return true;
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
