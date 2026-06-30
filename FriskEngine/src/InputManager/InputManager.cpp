#include "InputManager/InputManager.h"

namespace Frisk::Input {

	void InputManager::ConsumeEvent(const Event& e) {
		std::visit([this](const auto& event) {
			using T = std::decay_t<decltype(event)>;

			// start comparing types
			if constexpr (std::is_same_v<T, KeyEvent>) {
				switch (event.action) {
					case GLFW_PRESS: { this->SetKey(event.key, KeyStatus::JustPressed); break; }
					case GLFW_RELEASE: { this->SetKey(event.key, KeyStatus::Released); break; }
					case GLFW_REPEAT: { this->SetKey(event.key, KeyStatus::Held); break; }
				}
			}
			else if constexpr (std::is_same_v<T, MouseButtonEvent>) {
				switch (event.action) {
					case GLFW_PRESS: { this->SetButton(event.button, KeyStatus::JustPressed); break; }
					case GLFW_RELEASE: { this->SetButton(event.button, KeyStatus::Released); break; }
				}
			}
			}, e);
	}

	KeyStatus InputManager::GetKeyStatus(int keycode) {
		if (!isKeyValid(keycode)) return KeyStatus::Released;

		return m_Keys[getIndex(keycode)];
	}

	KeyStatus InputManager::GetButtonStatus(int button) {
		if (!isButtonValid(button)) return KeyStatus::Released;

		return m_Buttons[button];
	}

	void InputManager::getMousePos(double& xpos, double& ypos) const {
		xpos = m_MouseXPOS;
		ypos = m_MouseYPOS;
	}

	void InputManager::getMousePosDelta(double& dx, double& dy) {
		dx = m_MouseXPOS_DELTA;
		dy = m_MouseYPOS_DELTA;

		m_MouseXPOS_DELTA = 0;
		m_MouseYPOS_DELTA = 0;
	}

	void InputManager::HaltInputs() {
		memset(m_Keys, (int)KeyStatus::Buffer, KEY_COUNT);
		memset(m_Buttons, (int)KeyStatus::Buffer, BUTTON_COUNT);
	}

}