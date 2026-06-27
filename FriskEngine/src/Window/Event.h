#pragma once

namespace Frisk {


	enum EventIdentifier {
		KEY_EVENT_FLAG,
		MOUSE_BUTTON_FLAG,
		MOUSE_MOVE_FLAG

	};

	struct KeyEvent {
		int key;
		int action;
		int scancode;
		int mods;
		EventIdentifier flag = KEY_EVENT_FLAG;
	};

	struct MouseButtonEvent {
		int button;
		int action;
		int mods;
		EventIdentifier flag = MOUSE_BUTTON_FLAG;
	};

	struct MouseMoveEvent {
		double x;
		double y;
		EventIdentifier flag = MOUSE_MOVE_FLAG;
	};

	using Event = std::variant<KeyEvent, MouseButtonEvent, MouseMoveEvent>;
}