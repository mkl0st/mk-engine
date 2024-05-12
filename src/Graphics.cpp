#include <MK/Graphics.hpp>

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  (void)window;
  glViewport(0, 0, width, height);
}

mk::Graphics::Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
  // Shaders
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  // Shader Source Codes
  std::string vertexShaderSource = mk::File::getContents("resources/Shaders/default.vert");
  std::string fragmentShaderSource = mk::File::getContents("resources/Shaders/default.frag");

  const char* vertexShaderSourceC = vertexShaderSource.c_str();
  const char* fragmentShaderSourceC = fragmentShaderSource.c_str();

  glShaderSource(vertexShader, 1, &vertexShaderSourceC, NULL);
  glShaderSource(fragmentShader, 1, &fragmentShaderSourceC, NULL);

  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  // Info Log
  int success {0};
  char infoLog[mk::Constants::INFO_LOG_SIZE];

  // Validating the Vertex Shader
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, mk::Constants::INFO_LOG_SIZE, NULL, infoLog);
    std::cerr << "Failed to compile the vertex shader!\n";
    std::cerr << "Error: " << infoLog << '\n';
  }

  // Validating the Fragment Shader
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, mk::Constants::INFO_LOG_SIZE, NULL, infoLog);
    std::cerr << "Failed to compile the fragment shader!\n";
    std::cerr << "Error: " << infoLog << '\n';
  }

  // Shader Program
  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);

  // Validating the Shader Program
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(ID, mk::Constants::INFO_LOG_SIZE, NULL, infoLog);
    std::cerr << "Failed to link the shader program!\n";
    std::cerr << "Error: " << infoLog << '\n';
  }
}

void mk::Graphics::VAO::LinkAttrib(const mk::Graphics::VBO& VBO, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, const void* offset) const
{
  VBO.Bind();
  glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  VBO.Unbind();
}

void mk::Window::_initialize()
{
  glfwInstance = glfwCreateWindow(
    this->width,
    this->height,
    this->title.c_str(),
    NULL,
    NULL
  );
  if (glfwInstance == nullptr)
  {
    std::cerr << "Failed to create a GLFW window!\n";
    mk::Core::terminate();
  }
  glfwMakeContextCurrent(glfwInstance);
  glfwSetFramebufferSizeCallback(glfwInstance, framebufferSizeCallback);
}

void mk::Window::update()
{
  glfwPollEvents();
}

void mk::Window::clear()
{
  glClear(GL_COLOR_BUFFER_BIT);
}

void mk::Window::render()
{
  glfwSwapBuffers(glfwInstance);
}
