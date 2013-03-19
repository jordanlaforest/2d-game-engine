#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <GL/glew.h>
#include <GL/glfw.h>

#define NUM_KEYS GLFW_KEY_LAST + 1

namespace Input
{
  namespace Keys
  {
    //Defining these to allow for an eaiser swith between input libraries
    
    unsigned int const SPACE       = GLFW_KEY_SPACE;
    unsigned int const ESC         = GLFW_KEY_ESC;
    unsigned int const F1          = GLFW_KEY_F1;
    unsigned int const F2          = GLFW_KEY_F2;
    unsigned int const F3          = GLFW_KEY_F3;
    unsigned int const F4          = GLFW_KEY_F4;
    unsigned int const F5          = GLFW_KEY_F5;
    unsigned int const F6          = GLFW_KEY_F6;
    unsigned int const F7          = GLFW_KEY_F7;
    unsigned int const F8          = GLFW_KEY_F8;
    unsigned int const F9          = GLFW_KEY_F9;
    unsigned int const F10         = GLFW_KEY_F10;
    unsigned int const F11         = GLFW_KEY_F11;
    unsigned int const F12         = GLFW_KEY_F12;
    unsigned int const F13         = GLFW_KEY_F13;
    unsigned int const F14         = GLFW_KEY_F14;
    unsigned int const F15         = GLFW_KEY_F15;
    unsigned int const F16         = GLFW_KEY_F16;
    unsigned int const F17         = GLFW_KEY_F17;
    unsigned int const F18         = GLFW_KEY_F18;
    unsigned int const F19         = GLFW_KEY_F19;
    unsigned int const F20         = GLFW_KEY_F20;
    unsigned int const F21         = GLFW_KEY_F21;
    unsigned int const F22         = GLFW_KEY_F22;
    unsigned int const F23         = GLFW_KEY_F23;
    unsigned int const F24         = GLFW_KEY_F24;
    unsigned int const F25         = GLFW_KEY_F25;
    unsigned int const UP          = GLFW_KEY_UP         ;
    unsigned int const DOWN        = GLFW_KEY_DOWN;
    unsigned int const LEFT        = GLFW_KEY_LEFT;
    unsigned int const RIGHT       = GLFW_KEY_RIGHT;
    unsigned int const LSHIFT      = GLFW_KEY_LSHIFT;
    unsigned int const RSHIFT      = GLFW_KEY_RSHIFT;
    unsigned int const LCTRL       = GLFW_KEY_LCTRL;
    unsigned int const RCTRL       = GLFW_KEY_RCTRL;
    unsigned int const LALT        = GLFW_KEY_LALT;
    unsigned int const RALT        = GLFW_KEY_RALT;
    unsigned int const LSUPER      = GLFW_KEY_LSUPER;
    unsigned int const RSUPER      = GLFW_KEY_RSUPER;
    unsigned int const TAB         = GLFW_KEY_TAB;
    unsigned int const ENTER       = GLFW_KEY_ENTER;
    unsigned int const BACKSPACE   = GLFW_KEY_BACKSPACE;
    unsigned int const INSERT      = GLFW_KEY_INSERT;
    unsigned int const DEL         = GLFW_KEY_DEL;
    unsigned int const PAGEUP      = GLFW_KEY_PAGEUP;
    unsigned int const PAGEDOWN    = GLFW_KEY_PAGEDOWN;
    unsigned int const HOME        = GLFW_KEY_HOME;
    unsigned int const END         = GLFW_KEY_END;
    unsigned int const KP_1        = GLFW_KEY_KP_1;
    unsigned int const KP_2        = GLFW_KEY_KP_2;
    unsigned int const KP_3        = GLFW_KEY_KP_3;
    unsigned int const KP_4        = GLFW_KEY_KP_4;
    unsigned int const KP_5        = GLFW_KEY_KP_5;
    unsigned int const KP_6        = GLFW_KEY_KP_6;
    unsigned int const KP_7        = GLFW_KEY_KP_7;
    unsigned int const KP_8        = GLFW_KEY_KP_8;
    unsigned int const KP_9        = GLFW_KEY_KP_9;
    unsigned int const KP_DIVIDE   = GLFW_KEY_KP_DIVIDE;
    unsigned int const KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY;
    unsigned int const KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT;
    unsigned int const KP_ADD      = GLFW_KEY_KP_ADD;
    unsigned int const KP_DECIMAL  = GLFW_KEY_KP_DECIMAL;
    unsigned int const KP_EQUAL    = GLFW_KEY_KP_EQUAL;
    unsigned int const KP_ENTER    = GLFW_KEY_KP_ENTER;
    unsigned int const KP_NUM_LOCK = GLFW_KEY_KP_NUM_LOCK;
    unsigned int const CAPS_LOCK   = GLFW_KEY_CAPS_LOCK;
    unsigned int const SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK;
    unsigned int const PAUSE       = GLFW_KEY_PAUSE;
    unsigned int const MENU        = GLFW_KEY_MENU;
  }

  void initInput();
  bool getKeyState(std::string key);
  void addMapping(std::string name, int key);
}

#endif
