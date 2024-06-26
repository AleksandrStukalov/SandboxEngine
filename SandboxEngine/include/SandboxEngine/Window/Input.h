#pragma once

namespace SE
{
    enum class Key;
    enum class KeyMode;
    enum class MouseButton;

    unsigned int getPlatformKey(SE::Key key);
    unsigned int getPlatformKeyMode(SE::KeyMode mode);
    unsigned int getPlatformMouseButton(SE::MouseButton mouseButton);
    SE::Key getSEKey(unsigned int key);
    SE::KeyMode getSEkeyMode(unsigned int mode);
    SE::MouseButton getSEMouseButton(unsigned int mouseButton);

    enum class Key
    {
        NONE,
        /*Printable kays*/
        SPACE,
        APOSTROPHE,     /* ' */
        COMMA,          /* , */
        MINUS,          /* - */
        PERIOD,         /* . */
        SLASH,          /* / */
        ZERO,
        ONE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        SEMICOLON,      /* ; */
        EQUAL,          /* = */
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        LEFT_BRACKET,   /* [ */
        BACKSLASH,      /* \ */
        RIGHT_BRACKET,  /* ] */
        GRAVE_ACCENT,   /* ` */
        /* Function keys */
        ESCAPE,
        ENTER,
        TAB,
        BACKSPACE,
        INSERT,
        DELETE,
        RIGHT,
        LEFT,
        DOWN,
        UP,
        PAGE_UP,
        PAGE_DOWN,
        HOME,
        END,
        CAPS_LOCK,
        SCROLL_LOCK,
        NUM_LOCK,
        PRINT_SCREEN,
        PAUSE,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,
        F25,
        KP_0,
        KP_1,
        KP_2,
        KP_3,
        KP_4,
        KP_5,
        KP_6,
        KP_7,
        KP_8,
        KP_9,
        KP_DECIMAL,
        KP_DIVIDE,
        KP_MULTIPLY,
        KP_SUBTRACT,
        KP_ADD,
        KP_ENTER,
        KP_EQUAL,
        LEFT_SHIFT,
        LEFT_CONTROL,
        LEFT_ALT,
        LEFT_SUPER,
        RIGHT_SHIFT,
        RIGHT_CONTROL,
        RIGHT_ALT,
        RIGHT_SUPER,
        MENU
    };
    enum class KeyMode
    {
        SHIFT,
        CONTROL,
        ALT,
        SUPER,
        CAPS_LOCK,
        NUM_LOCK
    };
    enum class MouseButton
    {
        LEFT,
        RIGHT,
        MIDDLE,
        BUTTON_4,
        BUTTON_5,
        BUTTON_6,
        BUTTON_7,
        BUTTON_8,
    };
    enum class Scroll
    {
        UP,
        DOWN
    };
    enum class Action
    {
        PRESSED,
        RELEASED,
        TOGGLE // NOTE: Toggle means, that every time when user presses a key, flag, which corresponds to this key, is changed from false to true or vice versa.
    };
}