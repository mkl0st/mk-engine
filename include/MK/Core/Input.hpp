#ifndef MK_INPUT_HPP
#define MK_INPUT_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace mk
{
  /**
   * @brief Namespace for handling input events of the MK Engine.
   * @namespace Input
   */
  namespace Input
  {
    /**
     * @brief Enumeration representing various keyboard keys.
     * @enum Key
     */
    enum Key
    {
      Escape = GLFW_KEY_ESCAPE,
      Tab = GLFW_KEY_TAB,
      LeftShift = GLFW_KEY_LEFT_SHIFT,
      RightShift = GLFW_KEY_RIGHT_SHIFT,
      LeftControl = GLFW_KEY_LEFT_CONTROL,
      RightControl = GLFW_KEY_RIGHT_CONTROL,
      LeftAlt = GLFW_KEY_LEFT_ALT,
      RightAlt = GLFW_KEY_RIGHT_ALT,
      Spacebar = GLFW_KEY_SPACE,
      Backspace = GLFW_KEY_BACKSPACE,
      Num0 = GLFW_KEY_0,
      Num1 = GLFW_KEY_1,
      Num2 = GLFW_KEY_2,
      Num3 = GLFW_KEY_3,
      Num4 = GLFW_KEY_4,
      Num5 = GLFW_KEY_5,
      Num6 = GLFW_KEY_6,
      Num7 = GLFW_KEY_7,
      Num8 = GLFW_KEY_8,
      Num9 = GLFW_KEY_9,
      A = GLFW_KEY_A,
      B = GLFW_KEY_B,
      C = GLFW_KEY_C,
      D = GLFW_KEY_D,
      E = GLFW_KEY_E,
      F = GLFW_KEY_F,
      G = GLFW_KEY_G,
      H = GLFW_KEY_H,
      I = GLFW_KEY_I,
      J = GLFW_KEY_J,
      K = GLFW_KEY_K,
      L = GLFW_KEY_L,
      M = GLFW_KEY_M,
      N = GLFW_KEY_N,
      O = GLFW_KEY_O,
      P = GLFW_KEY_P,
      Q = GLFW_KEY_Q,
      R = GLFW_KEY_R,
      S = GLFW_KEY_S,
      T = GLFW_KEY_T,
      U = GLFW_KEY_U,
      V = GLFW_KEY_V,
      W = GLFW_KEY_W,
      X = GLFW_KEY_X,
      Y = GLFW_KEY_Y,
      Z = GLFW_KEY_Z,
    };
  }
}

#endif // MK_INPUT_HPP