#include "Input.h"

#include <GLFW/glfw3.h>

unsigned int SE::getPlatformKey(SE::Key key)
{
    switch (key)
    {
    case SE::Key::SPACE:            return GLFW_KEY_SPACE;
    case SE::Key::APOSTROPHE:       return GLFW_KEY_APOSTROPHE;
    case SE::Key::COMMA:            return GLFW_KEY_COMMA;
    case SE::Key::MINUS:            return GLFW_KEY_MINUS;
    case SE::Key::PERIOD:           return GLFW_KEY_PERIOD;
    case SE::Key::SLASH:            return GLFW_KEY_SLASH;
    case SE::Key::ZERO:             return GLFW_KEY_0;
    case SE::Key::ONE:              return GLFW_KEY_1;
    case SE::Key::TWO:              return GLFW_KEY_2;
    case SE::Key::THREE:            return GLFW_KEY_3;
    case SE::Key::FOUR:             return GLFW_KEY_4;
    case SE::Key::FIVE:             return GLFW_KEY_5;
    case SE::Key::SIX:              return GLFW_KEY_6;
    case SE::Key::SEVEN:            return GLFW_KEY_7;
    case SE::Key::EIGHT:            return GLFW_KEY_8;
    case SE::Key::NINE:             return GLFW_KEY_9;
    case SE::Key::SEMICOLON:        return GLFW_KEY_SEMICOLON;
    case SE::Key::EQUAL:            return GLFW_KEY_EQUAL;
    case SE::Key::A:                return GLFW_KEY_A;
    case SE::Key::B:                return GLFW_KEY_B;
    case SE::Key::C:                return GLFW_KEY_C;
    case SE::Key::D:                return GLFW_KEY_D;
    case SE::Key::E:                return GLFW_KEY_E;
    case SE::Key::F:                return GLFW_KEY_F;
    case SE::Key::G:                return GLFW_KEY_G;
    case SE::Key::H:                return GLFW_KEY_H;
    case SE::Key::I:                return GLFW_KEY_I;
    case SE::Key::J:                return GLFW_KEY_J;
    case SE::Key::K:                return GLFW_KEY_K;
    case SE::Key::L:                return GLFW_KEY_L;
    case SE::Key::M:                return GLFW_KEY_M;
    case SE::Key::N:                return GLFW_KEY_N;
    case SE::Key::O:                return GLFW_KEY_O;
    case SE::Key::P:                return GLFW_KEY_P;
    case SE::Key::Q:                return GLFW_KEY_Q;
    case SE::Key::R:                return GLFW_KEY_R;
    case SE::Key::S:                return GLFW_KEY_S;
    case SE::Key::T:                return GLFW_KEY_T;
    case SE::Key::U:                return GLFW_KEY_U;
    case SE::Key::V:                return GLFW_KEY_V;
    case SE::Key::W:                return GLFW_KEY_W;
    case SE::Key::X:                return GLFW_KEY_X;
    case SE::Key::Y:                return GLFW_KEY_Y;
    case SE::Key::Z:                return GLFW_KEY_Z;
    case SE::Key::LEFT_BRACKET:     return GLFW_KEY_LEFT_BRACKET;
    case SE::Key::BACKSLASH:        return GLFW_KEY_BACKSLASH;
    case SE::Key::RIGHT_BRACKET:    return GLFW_KEY_RIGHT_BRACKET;
    case SE::Key::GRAVE_ACCENT:     return GLFW_KEY_GRAVE_ACCENT;
    case SE::Key::ESCAPE:           return GLFW_KEY_ESCAPE;
    case SE::Key::ENTER:            return GLFW_KEY_ENTER;
    case SE::Key::TAB:              return GLFW_KEY_TAB;
    case SE::Key::BACKSPACE:        return GLFW_KEY_BACKSPACE;
    case SE::Key::INSERT:           return GLFW_KEY_INSERT;
    case SE::Key::DELETE:           return GLFW_KEY_DELETE;
    case SE::Key::RIGHT:            return GLFW_KEY_RIGHT;
    case SE::Key::LEFT:             return GLFW_KEY_LEFT;
    case SE::Key::DOWN:             return GLFW_KEY_DOWN;
    case SE::Key::UP:               return GLFW_KEY_UP;
    case SE::Key::PAGE_UP:          return GLFW_KEY_PAGE_UP;
    case SE::Key::PAGE_DOWN:        return GLFW_KEY_PAGE_DOWN;
    case SE::Key::HOME:             return GLFW_KEY_HOME;
    case SE::Key::END:              return GLFW_KEY_END;
    case SE::Key::CAPS_LOCK:        return GLFW_KEY_CAPS_LOCK;
    case SE::Key::SCROLL_LOCK:      return GLFW_KEY_SCROLL_LOCK;
    case SE::Key::NUM_LOCK:         return GLFW_KEY_NUM_LOCK;
    case SE::Key::PRINT_SCREEN:     return GLFW_KEY_PRINT_SCREEN;
    case SE::Key::PAUSE:            return GLFW_KEY_PAUSE;
    case SE::Key::F1:               return  GLFW_KEY_F1;
    case SE::Key::F2:               return  GLFW_KEY_F2;
    case SE::Key::F3:               return  GLFW_KEY_F3;
    case SE::Key::F4:               return  GLFW_KEY_F4;
    case SE::Key::F5:               return  GLFW_KEY_F5;
    case SE::Key::F6:               return  GLFW_KEY_F6;
    case SE::Key::F7:               return  GLFW_KEY_F7;
    case SE::Key::F8:               return  GLFW_KEY_F8;
    case SE::Key::F9:               return  GLFW_KEY_F9;
    case SE::Key::F10:              return  GLFW_KEY_F10;
    case SE::Key::F11:              return  GLFW_KEY_F11;
    case SE::Key::F12:              return  GLFW_KEY_F12;
    case SE::Key::F13:              return  GLFW_KEY_F13;
    case SE::Key::F14:              return  GLFW_KEY_F14;
    case SE::Key::F15:              return  GLFW_KEY_F15;
    case SE::Key::F16:              return  GLFW_KEY_F16;
    case SE::Key::F17:              return  GLFW_KEY_F17;
    case SE::Key::F18:              return  GLFW_KEY_F18;
    case SE::Key::F19:              return  GLFW_KEY_F19;
    case SE::Key::F20:              return	GLFW_KEY_F20;
    case SE::Key::F21:              return	GLFW_KEY_F21;
    case SE::Key::F22:              return	GLFW_KEY_F22;
    case SE::Key::F23:              return	GLFW_KEY_F23;
    case SE::Key::F24:              return	GLFW_KEY_F24;
    case SE::Key::F25:              return	GLFW_KEY_F25;
    case SE::Key::KP_0:             return	GLFW_KEY_KP_0;
    case SE::Key::KP_1:             return	GLFW_KEY_KP_1;
    case SE::Key::KP_2:             return	GLFW_KEY_KP_2;
    case SE::Key::KP_3:             return	GLFW_KEY_KP_3;
    case SE::Key::KP_4:             return	GLFW_KEY_KP_4;
    case SE::Key::KP_5:             return	GLFW_KEY_KP_5;
    case SE::Key::KP_6:             return	GLFW_KEY_KP_6;
    case SE::Key::KP_7:             return	GLFW_KEY_KP_7;
    case SE::Key::KP_8:             return	GLFW_KEY_KP_8;
    case SE::Key::KP_9:             return	GLFW_KEY_KP_9;
    case SE::Key::KP_DECIMAL:       return	GLFW_KEY_KP_DECIMAL;
    case SE::Key::KP_DIVIDE:        return	GLFW_KEY_KP_DIVIDE;
    case SE::Key::KP_MULTIPLY:      return	GLFW_KEY_KP_MULTIPLY;
    case SE::Key::KP_SUBTRACT:      return	GLFW_KEY_KP_SUBTRACT;
    case SE::Key::KP_ADD:           return	GLFW_KEY_KP_ADD;
    case SE::Key::KP_ENTER:         return	GLFW_KEY_KP_ENTER;
    case SE::Key::KP_EQUAL:         return	GLFW_KEY_KP_EQUAL;
    case SE::Key::LEFT_SHIFT:       return	GLFW_KEY_LEFT_SHIFT;
    case SE::Key::LEFT_CONTROL:     return	GLFW_KEY_LEFT_CONTROL;
    case SE::Key::LEFT_ALT:         return	GLFW_KEY_LEFT_ALT;
    case SE::Key::LEFT_SUPER:       return	GLFW_KEY_LEFT_SUPER;
    case SE::Key::RIGHT_SHIFT:      return	GLFW_KEY_RIGHT_SHIFT;
    case SE::Key::RIGHT_CONTROL:    return	GLFW_KEY_RIGHT_CONTROL;
    case SE::Key::RIGHT_ALT:        return	GLFW_KEY_RIGHT_ALT;
    case SE::Key::RIGHT_SUPER:      return	GLFW_KEY_RIGHT_SUPER;
    case SE::Key::MENU:             return	GLFW_KEY_MENU;

    default:                        SE::Log::warning({ "Unsupported key" }); return -1;
    }
}
unsigned int SE::getPlatformKeyMode(SE::KeyMode keyMode)
{
    switch (keyMode)
    {
    case SE::KeyMode::SHIFT:        return GLFW_MOD_SHIFT;
    case SE::KeyMode::CONTROL:      return GLFW_MOD_CONTROL;
    case SE::KeyMode::ALT:          return GLFW_MOD_ALT;
    case SE::KeyMode::SUPER:        return GLFW_MOD_SUPER;
    case SE::KeyMode::CAPS_LOCK:    return GLFW_MOD_CAPS_LOCK;
    case SE::KeyMode::NUM_LOCK:     return GLFW_MOD_NUM_LOCK;
    default:                        SE::Log::warning({ "Unsupported key mode" }); return -1;
    }
}
unsigned int SE::getPlatformMouseButton(SE::MouseButton mouseButton)
{
    switch (mouseButton)
    {
    case SE::MouseButton::LEFT:             return GLFW_MOUSE_BUTTON_LEFT;
    case SE::MouseButton::RIGHT:            return GLFW_MOUSE_BUTTON_RIGHT;
    case SE::MouseButton::MIDDLE:           return GLFW_MOUSE_BUTTON_MIDDLE;
    case SE::MouseButton::BUTTON_4:         return GLFW_MOUSE_BUTTON_4;
    case SE::MouseButton::BUTTON_5:         return GLFW_MOUSE_BUTTON_5;
    case SE::MouseButton::BUTTON_6:         return GLFW_MOUSE_BUTTON_6;
    case SE::MouseButton::BUTTON_7:         return GLFW_MOUSE_BUTTON_7;
    default:                                SE::Log::warning({ "Unsupported mouse button" }); return -1;
    }
}
SE::Key SE::getSEKey(unsigned int key)
{
    switch (key)
    {
    case GLFW_KEY_SPACE:            return SE::Key::SPACE;
    case GLFW_KEY_APOSTROPHE:       return SE::Key::APOSTROPHE;
    case GLFW_KEY_COMMA:            return SE::Key::COMMA;
    case GLFW_KEY_MINUS:            return SE::Key::MINUS;
    case GLFW_KEY_PERIOD:           return SE::Key::PERIOD;
    case GLFW_KEY_SLASH:            return SE::Key::SLASH;
    case GLFW_KEY_0:                return SE::Key::ZERO;
    case GLFW_KEY_1:                return SE::Key::ONE;
    case GLFW_KEY_2:                return SE::Key::TWO;
    case GLFW_KEY_3:                return SE::Key::THREE;
    case GLFW_KEY_4:                return SE::Key::FOUR;
    case GLFW_KEY_5:                return SE::Key::FIVE;
    case GLFW_KEY_6:                return SE::Key::SIX;
    case GLFW_KEY_7:                return SE::Key::SEVEN;
    case GLFW_KEY_8:                return SE::Key::EIGHT;
    case GLFW_KEY_9:                return SE::Key::NINE;
    case GLFW_KEY_SEMICOLON:        return SE::Key::SEMICOLON;
    case GLFW_KEY_EQUAL:            return SE::Key::EQUAL;
    case GLFW_KEY_A:                return SE::Key::A;
    case GLFW_KEY_B:                return SE::Key::B;
    case GLFW_KEY_C:                return SE::Key::C;
    case GLFW_KEY_D:                return SE::Key::D;
    case GLFW_KEY_E:                return SE::Key::E;
    case GLFW_KEY_F:                return SE::Key::F;
    case GLFW_KEY_G:                return SE::Key::G;
    case GLFW_KEY_H:                return SE::Key::H;
    case GLFW_KEY_I:                return SE::Key::I;
    case GLFW_KEY_J:                return SE::Key::J;
    case GLFW_KEY_K:                return SE::Key::K;
    case GLFW_KEY_L:                return SE::Key::L;
    case GLFW_KEY_M:                return SE::Key::M;
    case GLFW_KEY_N:                return SE::Key::N;
    case GLFW_KEY_O:                return SE::Key::O;
    case GLFW_KEY_P:                return SE::Key::P;
    case GLFW_KEY_Q:                return SE::Key::Q;
    case GLFW_KEY_R:                return SE::Key::R;
    case GLFW_KEY_S:                return SE::Key::S;
    case GLFW_KEY_T:                return SE::Key::T;
    case GLFW_KEY_U:                return SE::Key::U;
    case GLFW_KEY_V:                return SE::Key::V;
    case GLFW_KEY_W:                return SE::Key::W;
    case GLFW_KEY_X:                return SE::Key::X;
    case GLFW_KEY_Y:                return SE::Key::Y;
    case GLFW_KEY_Z:                return SE::Key::Z;
    case GLFW_KEY_LEFT_BRACKET:     return SE::Key::LEFT_BRACKET;
    case GLFW_KEY_BACKSLASH:        return SE::Key::BACKSLASH;
    case GLFW_KEY_RIGHT_BRACKET:    return SE::Key::RIGHT_BRACKET;
    case GLFW_KEY_GRAVE_ACCENT:     return SE::Key::GRAVE_ACCENT;
    case GLFW_KEY_ESCAPE:           return SE::Key::ESCAPE;
    case GLFW_KEY_ENTER:            return SE::Key::ENTER;
    case GLFW_KEY_TAB:              return SE::Key::TAB;
    case GLFW_KEY_BACKSPACE:        return SE::Key::BACKSPACE;
    case GLFW_KEY_INSERT:           return SE::Key::INSERT;
    case GLFW_KEY_DELETE:           return SE::Key::DELETE;
    case GLFW_KEY_RIGHT:            return SE::Key::RIGHT;
    case GLFW_KEY_LEFT:             return SE::Key::LEFT;
    case GLFW_KEY_DOWN:             return SE::Key::DOWN;
    case GLFW_KEY_UP:               return SE::Key::UP;
    case GLFW_KEY_PAGE_UP:          return SE::Key::PAGE_UP;
    case GLFW_KEY_PAGE_DOWN:        return SE::Key::PAGE_DOWN;
    case GLFW_KEY_HOME:             return SE::Key::HOME;
    case GLFW_KEY_END:              return SE::Key::END;
    case GLFW_KEY_CAPS_LOCK:        return SE::Key::CAPS_LOCK;
    case GLFW_KEY_SCROLL_LOCK:      return SE::Key::SCROLL_LOCK;
    case GLFW_KEY_NUM_LOCK:         return SE::Key::NUM_LOCK;
    case GLFW_KEY_PRINT_SCREEN:     return SE::Key::PRINT_SCREEN;
    case GLFW_KEY_PAUSE:            return SE::Key::PAUSE;
    case GLFW_KEY_F1:               return SE::Key::F1;
    case GLFW_KEY_F2:               return SE::Key::F2;
    case GLFW_KEY_F3:               return SE::Key::F3;
    case GLFW_KEY_F4:               return SE::Key::F4;
    case GLFW_KEY_F5:               return SE::Key::F5;
    case GLFW_KEY_F6:               return SE::Key::F6;
    case GLFW_KEY_F7:               return SE::Key::F7;
    case GLFW_KEY_F8:               return SE::Key::F8;
    case GLFW_KEY_F9:               return SE::Key::F9;
    case GLFW_KEY_F10:              return SE::Key::F10;
    case GLFW_KEY_F11:              return SE::Key::F11;
    case GLFW_KEY_F12:              return SE::Key::F12;
    case GLFW_KEY_F13:              return SE::Key::F13;
    case GLFW_KEY_F14:              return SE::Key::F14;
    case GLFW_KEY_F15:              return SE::Key::F15;
    case GLFW_KEY_F16:              return SE::Key::F16;
    case GLFW_KEY_F17:              return SE::Key::F17;
    case GLFW_KEY_F18:              return SE::Key::F18;
    case GLFW_KEY_F19:              return SE::Key::F19;
    case GLFW_KEY_F20:              return SE::Key::F20;
    case GLFW_KEY_F21:              return SE::Key::F21;
    case GLFW_KEY_F22:              return SE::Key::F22;
    case GLFW_KEY_F23:              return SE::Key::F23;
    case GLFW_KEY_F24:              return SE::Key::F24;
    case GLFW_KEY_F25:              return SE::Key::F25;
    case GLFW_KEY_KP_0:             return SE::Key::KP_0;
    case GLFW_KEY_KP_1:             return SE::Key::KP_1;
    case GLFW_KEY_KP_2:             return SE::Key::KP_2;
    case GLFW_KEY_KP_3:             return SE::Key::KP_3;
    case GLFW_KEY_KP_4:             return SE::Key::KP_4;
    case GLFW_KEY_KP_5:             return SE::Key::KP_5;
    case GLFW_KEY_KP_6:             return SE::Key::KP_6;
    case GLFW_KEY_KP_7:             return SE::Key::KP_7;
    case GLFW_KEY_KP_8:             return SE::Key::KP_8;
    case GLFW_KEY_KP_9:             return SE::Key::KP_9;
    case GLFW_KEY_KP_DECIMAL:       return SE::Key::KP_DECIMAL;
    case GLFW_KEY_KP_DIVIDE:        return SE::Key::KP_DIVIDE;
    case GLFW_KEY_KP_MULTIPLY:      return SE::Key::KP_MULTIPLY;
    case GLFW_KEY_KP_SUBTRACT:      return SE::Key::KP_SUBTRACT;
    case GLFW_KEY_KP_ADD:           return SE::Key::KP_ADD;
    case GLFW_KEY_KP_ENTER:         return SE::Key::KP_ENTER;
    case GLFW_KEY_KP_EQUAL:         return SE::Key::KP_EQUAL;
    case GLFW_KEY_LEFT_SHIFT:       return SE::Key::LEFT_SHIFT;
    case GLFW_KEY_LEFT_CONTROL:     return SE::Key::LEFT_CONTROL;
    case GLFW_KEY_LEFT_ALT:         return SE::Key::LEFT_ALT;
    case GLFW_KEY_LEFT_SUPER:       return SE::Key::LEFT_SUPER;
    case GLFW_KEY_RIGHT_SHIFT:      return SE::Key::RIGHT_SHIFT;
    case GLFW_KEY_RIGHT_CONTROL:    return SE::Key::RIGHT_CONTROL;
    case GLFW_KEY_RIGHT_ALT:        return SE::Key::RIGHT_ALT;
    case GLFW_KEY_RIGHT_SUPER:      return SE::Key::RIGHT_SUPER;
    case GLFW_KEY_MENU:             return SE::Key::MENU;

    default:                        SE::Log::warning({ "Unsupported key" }); return SE::Key();
    }
}
SE::KeyMode SE::getSEkeyMode(unsigned int mode)
{
    switch (mode)
    {
    case GLFW_MOD_SHIFT:        return SE::KeyMode::SHIFT;
    case GLFW_MOD_CONTROL:      return SE::KeyMode::CONTROL;
    case GLFW_MOD_ALT:          return SE::KeyMode::ALT;
    case GLFW_MOD_SUPER:        return SE::KeyMode::SUPER;
    case GLFW_MOD_CAPS_LOCK:    return SE::KeyMode::CAPS_LOCK;
    case GLFW_MOD_NUM_LOCK:     return SE::KeyMode::NUM_LOCK;
    default:                    SE::Log::warning({ "Unsupported key mode" }); return SE::KeyMode();
    }
}
SE::MouseButton SE::getSEMouseButton(unsigned int mouseButton)
{
    switch (mouseButton)
    {
    case GLFW_MOUSE_BUTTON_LEFT:        return SE::MouseButton::LEFT;
    case GLFW_MOUSE_BUTTON_RIGHT:       return SE::MouseButton::RIGHT;
    case GLFW_MOUSE_BUTTON_MIDDLE:      return SE::MouseButton::MIDDLE;
    case GLFW_MOUSE_BUTTON_4:           return SE::MouseButton::BUTTON_4;
    case GLFW_MOUSE_BUTTON_5:           return SE::MouseButton::BUTTON_5;
    case GLFW_MOUSE_BUTTON_6:           return SE::MouseButton::BUTTON_6;
    case GLFW_MOUSE_BUTTON_7:           return SE::MouseButton::BUTTON_7;
    default:                            SE::Log::warning({ "Unsupported mouse button" }); return SE::MouseButton();
    }
}