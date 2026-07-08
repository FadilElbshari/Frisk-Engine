#include "InputManager/InputManager.h"

namespace Frisk::Input
{

    void InputManager::ConsumeEvent(const Event &e)
    {
        std::visit(
            [this](const auto &event)
            {
                using T = std::decay_t<decltype(event)>;

                // start comparing types
                if constexpr (std::is_same_v<T, KeyEvent>)
                {
                    switch (event.action)
                    {
                        case GLFW_PRESS:
                        {
                            this->SetKey(event.key, KeyStatus::JustPressed);
                            break;
                        }
                        case GLFW_RELEASE:
                        {
                            this->SetKey(event.key, KeyStatus::JustReleased);
                            break;
                        }
                    }
                }
                else if constexpr (std::is_same_v<T, MouseButtonEvent>)
                {
                    switch (event.action)
                    {
                        case GLFW_PRESS:
                        {
                            this->SetButton(event.button, KeyStatus::JustPressed);
                            break;
                        }
                        case GLFW_RELEASE:
                        {
                            this->SetButton(event.button, KeyStatus::JustReleased);
                            break;
                        }
                    }
                }
            },
            e);
    }

    KeyStatus InputManager::GetKeyStatus(int keycode)
    {
        if (!isKeyValid(keycode))
            return KeyStatus::Released;

        return m_Keys[getIndex(keycode)];
    }

    KeyStatus InputManager::GetButtonStatus(int button)
    {
        if (!isButtonValid(button))
            return KeyStatus::Released;

        return m_Buttons[button];
    }

    void InputManager::getMousePos(double &xpos, double &ypos) const
    {
        xpos = m_MouseXPOS;
        ypos = m_MouseYPOS;
    }

    void InputManager::getMousePosDelta(double &dx, double &dy)
    {
        dx = m_MouseXPOS_DELTA;
        dy = m_MouseYPOS_DELTA;

        m_MouseXPOS_DELTA = 0;
        m_MouseYPOS_DELTA = 0;
    }

    void InputManager::Update()
    {
        for (U32 i{}; i < KEY_COUNT; i++)
        {
            auto& key_state = m_Keys[i];
            if (key_state == KeyStatus::JustPressed)
            {
                key_state = KeyStatus::Pressed;
            } else if (key_state == KeyStatus::JustReleased) key_state = KeyStatus::Released;
        }

        for (U32 i{}; i < BUTTON_COUNT; i++)
        {
            auto& key_state = m_Buttons[i];
            if (key_state == KeyStatus::JustPressed)
            {
                key_state = KeyStatus::Pressed;
            } else if (key_state == KeyStatus::JustReleased) key_state = KeyStatus::Released;
        }
    }

    void InputManager::setMousePos(const VEC2& pos)
    {
        m_MouseXPOS_LAST = m_MouseXPOS;
        m_MouseYPOS_LAST = m_MouseYPOS;

        if (m_FirstRecord)
        {
            m_MouseXPOS_LAST = pos.x;
            m_MouseYPOS_LAST = pos.y;
            m_FirstRecord = false;
        }


        m_MouseXPOS = pos.x;
        m_MouseYPOS = pos.y;

        m_MouseXPOS_DELTA = m_MouseXPOS - m_MouseXPOS_LAST;
        m_MouseYPOS_DELTA = m_MouseYPOS_LAST - m_MouseYPOS;
    }

} // namespace Frisk::Input
