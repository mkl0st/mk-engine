#include <MK/Graphics.hpp>

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  mk::Window* windowInstance = static_cast<mk::Window*>(glfwGetWindowUserPointer(window));

  windowInstance->setBufferDimensions({
    static_cast<float>(width),
    static_cast<float>(height),
  });
  for (auto& renderer : windowInstance->getRenderers())
    renderer->getCamera().setBufferDimensions({
      static_cast<float>(width),
      static_cast<float>(height),
    });
}

const std::array<GLuint, 6> rectangleIndices =
{
  0, 1, 3,
  0, 3, 2,
};

std::array<GLfloat, 4 * 3> generateRectangleVertices(const float width, const float height)
{
  return {
    -width / 2.f,  height / 2.f, 0.f,
     width / 2.f,  height / 2.f, 0.f,
    -width / 2.f, -height / 2.f, 0.f,
     width / 2.f, -height / 2.f, 0.f,
  };
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
  glfwSetWindowUserPointer(glfwInstance, this);
  glfwSetFramebufferSizeCallback(glfwInstance, framebufferSizeCallback);
  glClearColor(
    clearColor.red,
    clearColor.green,
    clearColor.blue,
    clearColor.alpha
  );
}

void mk::Window::_updateDeltaTime()
{
  float currentTime = static_cast<float>(glfwGetTime());
  deltaTime = currentTime - lastTime;
  lastTime = currentTime;
}

void mk::Window::maximize()
{
  int xPos;
  int yPos;
  glfwGetWindowPos(glfwInstance, &xPos, &yPos);

  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);

  cachedX = xPos;
  cachedY = yPos;
  cachedWidth = width;
  cachedHeight = height;

  glfwSetWindowMonitor(
    glfwInstance,
    monitor,
    0,
    0,
    mode->width,
    mode->height,
    mode->refreshRate
  );
  isMaximized = true;
}

void mk::Window::unmaximize()
{
  glfwSetWindowMonitor(
    glfwInstance,
    0,
    cachedX,
    cachedY,
    cachedWidth,
    cachedHeight,
    0
  );
  isMaximized = false;
}

void mk::Window::update()
{
  glfwPollEvents();
  _updateDeltaTime();
}

void mk::Window::clear()
{
  glClear(GL_COLOR_BUFFER_BIT);
}

void mk::Window::display()
{
  glfwSwapBuffers(glfwInstance);
}

void mk::Window::addRenderer(const mk::Render::Renderer& renderer)
{
  auto it = std::find_if(
    renderers.begin(),
    renderers.end(),
    [&renderer](const mk::Render::Renderer* r)
    {
      return r == &renderer;
    }
  );
  if (it == renderers.end())
  {
    renderers.push_back(const_cast<mk::Render::Renderer*>(&renderer));
  }
}

void mk::Window::removeRenderer(const mk::Render::Renderer& renderer)
{
  auto it = std::find_if(
    renderers.begin(),
    renderers.end(),
    [&renderer](const mk::Render::Renderer* r)
    {
      return r == &renderer;
    }
  );
  if (it != renderers.end())
  {
    renderers.erase(it);
  }
}

void mk::Render::Renderer::use()
{
  shader.Use();
  camera.updateMatrix();
  camera.applyMatrix(shader);
}

void mk::Render::Renderer::render(const mk::Shapes::Shape& shape) const
{
  mk::Space::Vec2 offset = {shape.getBounds().width / 2.f, shape.getBounds().height / 2.f};
  mk::Space::Mat4 model =
    mk::Space::scale({1.f}, shape.getScale()) *
    mk::Space::rotate({1.f} ,{0.f, 0.f, 1.f}, shape.getRotation()) *
    mk::Space::translate({1.f}, shape.getPosition() + offset);

  shape.getVAO()->Bind();
  shader.SetMat4("model", model);
  shader.SetVec3("fillColor", shape.getFillColor().toRGBVec());
  glDrawElements(GL_TRIANGLES, shape.getIndexCount(), GL_UNSIGNED_INT, NULL);
  shape.getVAO()->Unbind();
}

mk::Shapes::Rectangle::Rectangle(const mk::Space::Vec2& position, const float width, const float height)
: mk::Shapes::Shape(position, 6), width(width), height(height)
{
  VAO = new mk::Graphics::VAO();
  VBO = new mk::Graphics::VBO(generateRectangleVertices(width, height));
  EBO = new mk::Graphics::EBO(rectangleIndices);

  VAO->Bind();
  VBO->Bind();
  EBO->Bind();

  VAO->LinkAttrib(*VBO, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);

  VAO->Unbind();
  VBO->Unbind();
  EBO->Unbind();
}

void mk::Camera2D::updateMatrix()
{
  constexpr float targetAspect =
    static_cast<float>(mk::Constants::RENDER_WIDTH) / static_cast<float>(mk::Constants::RENDER_HEIGHT);

  float aspectWidth = bufferDimensions.x;
  float aspectHeight = bufferDimensions.x / targetAspect;

  if (aspectHeight > bufferDimensions.y)
  {
    aspectHeight = bufferDimensions.y;
    aspectWidth = aspectHeight * targetAspect;
  }

  float paddingTop = bufferDimensions.y / 2.f - aspectHeight / 2.f;
  float paddingLeft = bufferDimensions.x / 2.f - aspectWidth / 2.f;

  glViewport
  (
    paddingLeft,
    paddingTop,
    aspectWidth,
    aspectHeight
  );
  mk::Space::Mat4 projection = mk::Space::ortho(
    0.f,
    mk::Constants::RENDER_WIDTH,
    0.f,
    mk::Constants::RENDER_HEIGHT,
    -1.f,
    1.f
  );

  matrix = projection;
}
