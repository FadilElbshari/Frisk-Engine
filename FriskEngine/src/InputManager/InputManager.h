#pragma once

namespace Frisk::Input {
	class InputManager {

	public:
		InputManager() = default;
		~InputManager() = default;

		void setKey(int keycode, bool isActive) {
			if (!isKeyValid(keycode)) return;

			m_Keys[getIndex(keycode)] = isActive;
		}

		bool isKeyDown(int keycode) {
			if (!isKeyValid(keycode)) return false;

			return m_Keys[getIndex(keycode)];
		}

		void setButton(int button, bool isActive) {
			if (!isButtonValid(button)) return;

			m_Buttons[button] = isActive;
		}

		bool isButtonDown(int button) {
			if (!isButtonValid(button)) return false;

			return m_Buttons[button];
		}

		void setMousePos(double xpos, double ypos) {
			m_MouseXPOS_LAST = m_MouseXPOS;
			m_MouseYPOS_LAST = m_MouseYPOS;

			m_MouseXPOS = xpos;
			m_MouseYPOS = ypos;

			m_MouseXPOS_DELTA = m_MouseXPOS - m_MouseXPOS_LAST;
			m_MouseYPOS_DELTA = m_MouseYPOS_LAST - m_MouseYPOS;

		}

		void getMousePos(double& xpos, double& ypos) const {
			xpos = m_MouseXPOS;
			ypos = m_MouseYPOS;
		}

		void getMousePosDelta(double& dx, double& dy) {
			dx = m_MouseXPOS_DELTA;
			dy = m_MouseYPOS_DELTA;

			m_MouseXPOS_DELTA = 0;
			m_MouseYPOS_DELTA = 0;
		}

	private:

		static constexpr int KEY_OFFSET = 32;
		static constexpr int KEY_COUNT = 317;

		static constexpr int BUTTON_COUNT = 8;

		bool m_Keys[KEY_COUNT] = {};
		bool m_Buttons[BUTTON_COUNT] = {};

		double m_MouseXPOS = 0;
		double m_MouseYPOS = 0;

		double m_MouseXPOS_LAST = 0;
		double m_MouseYPOS_LAST = 0;

		double m_MouseXPOS_DELTA = 0;
		double m_MouseYPOS_DELTA = 0;

		inline bool isKeyValid(int keycode) { return keycode >= KEY_OFFSET && keycode < KEY_OFFSET + KEY_COUNT; }
		inline int getIndex(int keycode) { return keycode - KEY_OFFSET; }

		inline bool isButtonValid(int button) { return button >= 0 && button < BUTTON_COUNT; }
	};
}