#pragma once
#include "../Core/Events.h"
#include <SFML\Window.hpp>

namespace GF {
	namespace IOModule {
		namespace Events {
			typedef Core::Events::EventArgs EventArgs;
#define CREATE_CONVERSION_CONSTRUCT(NAME, TYPE) NAME(TYPE& ev) {*(TYPE*)this = ev;} NAME()=default;
			struct KeyboardArgs : public EventArgs, public sf::Event::KeyEvent {
				CREATE_CONVERSION_CONSTRUCT(KeyboardArgs, sf::Event::KeyEvent);
				typedef sf::Keyboard::Key KeyCode;
			};

			struct MouseButtArgs : public EventArgs, public sf::Event::MouseButtonEvent {
				CREATE_CONVERSION_CONSTRUCT(MouseButtArgs, sf::Event::MouseButtonEvent);
				typedef sf::Mouse::Button ButtonCode;
			};

			struct MouseMoveArgs : public EventArgs, public sf::Event::MouseMoveEvent {
				CREATE_CONVERSION_CONSTRUCT(MouseMoveArgs, sf::Event::MouseMoveEvent);
			};

			struct MouseWheelArgs :public EventArgs, public sf::Event::MouseWheelEvent {
				CREATE_CONVERSION_CONSTRUCT(MouseWheelArgs, sf::Event::MouseWheelEvent);
			};

			struct JoystickButtArgs : public EventArgs, public sf::Event::JoystickButtonEvent {
				CREATE_CONVERSION_CONSTRUCT(JoystickButtArgs, sf::Event::JoystickButtonEvent);
			};

			struct JoystickMoveArgs : public EventArgs, public sf::Event::JoystickMoveEvent {
				CREATE_CONVERSION_CONSTRUCT(JoystickMoveArgs, sf::Event::JoystickMoveEvent);
				typedef sf::Joystick::Axis Axis;
			};

			struct JoystickArgs : public EventArgs, public sf::Event::JoystickConnectEvent {
				CREATE_CONVERSION_CONSTRUCT(JoystickArgs, sf::Event::JoystickConnectEvent);
			};

			struct ResizeArgs :public EventArgs, public sf::Event::SizeEvent {
				CREATE_CONVERSION_CONSTRUCT(ResizeArgs, sf::Event::SizeEvent);
			};

			struct TextTypeArgs :public EventArgs, public sf::Event::TextEvent {
				CREATE_CONVERSION_CONSTRUCT(TextTypeArgs, sf::Event::TextEvent);
			};
#undef CREATE_CONVERSION_CONSTRUCT
		}
	}
}