#pragma once
#include <functional>
#include <list>
#include <SFML\Window.hpp>

namespace GameFramework {
	namespace IOModule {
		namespace Events {
			template<typename ArgType> class Event {
			public:
				void operator+=(std::function<void(void*, ArgType&)>&);
				void operator-=(std::function<void(void*, ArgType&)>&);
				void operator()(void*, ArgType&);
				unsigned size();
			private:
				std::list < std::function<void(void*, ArgType&)>> funcs;
			};

			struct EventArgs {
				int timestamp;
				bool cancel;
			};

			struct KeyboardArgs : EventArgs, sf::Event::KeyEvent {
				typedef sf::Keyboard::Key KeyCode;
				KeyCode code;
			};

			struct MouseButtArgs : EventArgs, sf::Event::MouseButtonEvent {
				typedef sf::Mouse::Button ButtonCode;
				ButtonCode button;
			};

			struct MouseMoveArgs : EventArgs, sf::Event::MouseMoveEvent {};

			struct MouseWheelArgs :EventArgs, sf::Event::MouseWheelEvent {};

			struct JoystickButtArgs : EventArgs, sf::Event::JoystickButtonEvent {};

			struct JoystickMoveArgs : EventArgs, sf::Event::JoystickMoveEvent {
				typedef sf::Joystick::Axis Axis;
				Axis axis;
			};

			struct JoystickArgs : EventArgs, sf::Event::JoystickConnectEvent {};

			struct ResizeArgs:EventArgs, sf::Event::SizeEvent{};
		}
	}
}