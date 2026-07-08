#pragma once

#include "Window/Event.h"

namespace Frisk::Input
{

    enum class KeyStatus
    {
        Released,
        Pressed,
        JustReleased,
        JustPressed
    };

    class InputManager
    {

      public:
        InputManager() = default;
        ~InputManager() = default;

        void ConsumeEvent(const Event &e);

        KeyStatus GetKeyStatus(int keycode);
        KeyStatus GetButtonStatus(int button);

        void getMousePos(double &xpos, double &ypos) const;
        void getMousePosDelta(double &dx, double &dy);
        void setMousePos(const VEC2& pos);

        void Update();

      private:
        static constexpr int KEY_OFFSET = 32;
        static constexpr int KEY_COUNT = 317;

        static constexpr int BUTTON_COUNT = 8;

        KeyStatus m_Keys[KEY_COUNT] = {};
        KeyStatus m_Buttons[BUTTON_COUNT] = {};

        double m_MouseXPOS = 0;
        double m_MouseYPOS = 0;

        double m_MouseXPOS_LAST = 0;
        double m_MouseYPOS_LAST = 0;

        double m_MouseXPOS_DELTA = 0;
        double m_MouseYPOS_DELTA = 0;

        bool m_FirstRecord = true;

        // helper inlines
        inline bool isKeyValid(int keycode) { return keycode >= KEY_OFFSET && keycode < KEY_OFFSET + KEY_COUNT; }
        inline int getIndex(int keycode) { return keycode - KEY_OFFSET; }
        inline bool isButtonValid(int button) { return button >= 0 && button < BUTTON_COUNT; }

        // setter functions
        void SetKey(int keycode, KeyStatus state)
        {
            if (!isKeyValid(keycode))
                return;

            m_Keys[getIndex(keycode)] = state;
        }

        void SetButton(int button, KeyStatus state)
        {
            if (!isButtonValid(button))
                return;

            m_Buttons[button] = state;
        }


    };
} // namespace Frisk::Input
