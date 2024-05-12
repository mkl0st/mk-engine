#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include <MK/Core.hpp>
#include <MK/Graphics.hpp>

// Window Settings
constexpr unsigned int WINDOW_WIDTH  {800u};
constexpr unsigned int WINDOW_HEIGHT {600u};
const     std::string  WINDOW_TITLE  {"MK Engine"};

// Constants
constexpr unsigned int INFO_LOG_SIZE {512u};

// Shader Source Codes
const char* vertexShaderSource =
  "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "layout (location = 1) in vec3 aCol;\n"
  "out vec3 vertCol;\n"
  "void main()\n"
  "{\n"
  "  vertCol = aCol;\n"
  "  gl_Position = vec4(aPos, 1.f);\n"
  "}\0";
const char* fragmentShaderSource =
  "#version 330 core\n"
  "in vec3 vertCol;\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "  FragColor = vec4(vertCol, 1.f);\n"
  "}\0";

// Vertices and Indices
const GLfloat vertices[] =
{
  -0.5f,  -0.5f, 0.f, 1.f, 1.f, 1.f,
   0.0f,  -0.5f, 0.f, 1.f, 1.f, 1.f,
   0.5f,  -0.5f, 0.f, 1.f, 1.f, 1.f,
  -0.25f,  0.0f, 0.f, 1.f, 1.f, 1.f,
   0.25f,  0.0f, 0.f, 1.f, 1.f, 1.f,
   0.0f,   0.5f, 0.f, 1.f, 1.f, 1.f,
};
const GLuint indices[] =
{
  0, 1, 3,
  1, 2, 4,
  3, 4, 5,
};

int main()
{
  // Initializing GLFW
  mk::Core::initializeGLFW();

  // Creating a Window
  GLFWwindow* window = glfwCreateWindow(
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    WINDOW_TITLE.c_str(),
    NULL,
    NULL
  );
  if (window == nullptr)
  {
    std::cerr << "Failed to create a GLFW window!\n";
    glfwTerminate();
    return EXIT_FAILURE;
  }
  glfwMakeContextCurrent(window);

  // Initializing GLEW
  if (!mk::Core::initializeGLEW())
  {
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_FAILURE;
  }

  // Clear Color
  mk::Color::RGBA clearColor {0, 0, 0, 1.f};
  glClearColor(
    clearColor.red,
    clearColor.green,
    clearColor.blue,
    clearColor.alpha
  );

  // Shaders
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  // Info Log
  int success {0};
  char infoLog[INFO_LOG_SIZE];

  // Validating the Vertex Shader
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, INFO_LOG_SIZE, NULL, infoLog);
    std::cerr << "Failed to compile the vertex shader!\n";
    std::cerr << "Error: " << infoLog << '\n';
  }

  // Validating the Fragment Shader
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, INFO_LOG_SIZE, NULL, infoLog);
    std::cerr << "Failed to compile the fragment shader!\n";
    std::cerr << "Error: " << infoLog << '\n';
  }

  // Shader Program
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // Validating the Shader Program
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(shaderProgram, INFO_LOG_SIZE, NULL, infoLog);
    std::cerr << "Failed to link the shader program!\n";
    std::cerr << "Error: " << infoLog << '\n';
  }

  // VAO, VBO, and EBO
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // Printing Engine and Version Info
  mk::Core::printEngineInfo();
  std::cout << '\n';
  mk::Core::printVersionInfo();

  // Main Loop
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
    glfwSwapBuffers(window);
  }

  // Program Termination
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glfwDestroyWindow(window);
  glfwTerminate();
  return EXIT_SUCCESS;
}
