#pragma once
#include "../stdafx.h"
#include <list>
#include <SFML\Window.hpp>

namespace GameFramework {
	namespace IOModule {
		namespace Events {
			static unsigned long long int lastId;
#define CREATE_CONVERSION_CONSTRUCT(NAME, TYPE) NAME(TYPE& ev) {*(TYPE*)this = ev;}
			template<typename ArgType> class Event {//TODO poprawiæ tak, aby nie trzeba przechowywaæ identyfikatora, a zarazem da³o siê u¿ywaæ std::function i std::bind
			private:
				template<typename ArgType> struct FuncWithID{
					std::function<void(void*, ArgType&)> func;
					int id;
					FuncWithID(std::function<void(void*, ArgType&)>& f) { id = lastId++; func = f; }
					FuncWithID(int& i) { id = i;}
					bool operator==(const FuncWithID& com) {
						return(com.id == this->id);
					}
					bool operator==(const int com) {
						return(com == this->id);
					}
				};
			public:
				int operator+=(std::function<void(void*, ArgType&)>);
				void operator-=(int id);
				void operator()(void*, ArgType&);
				unsigned size();
				void clear();
			private:
				std::list <FuncWithID<ArgType>> funcs;
			};

			struct EventArgs {
				int timestamp=0;
				bool cancel=false;
			};

			struct KeyboardArgs : EventArgs, sf::Event::KeyEvent {
				CREATE_CONVERSION_CONSTRUCT(KeyboardArgs, sf::Event::KeyEvent);
				typedef sf::Keyboard::Key KeyCode;
			};

			struct MouseButtArgs : EventArgs, sf::Event::MouseButtonEvent {
				CREATE_CONVERSION_CONSTRUCT(MouseButtArgs, sf::Event::MouseButtonEvent);
				typedef sf::Mouse::Button ButtonCode;
			};

			struct MouseMoveArgs : EventArgs, sf::Event::MouseMoveEvent {
				CREATE_CONVERSION_CONSTRUCT(MouseMoveArgs, sf::Event::MouseMoveEvent);
			};

			struct MouseWheelArgs :EventArgs, sf::Event::MouseWheelEvent {
				CREATE_CONVERSION_CONSTRUCT(MouseWheelArgs, sf::Event::MouseWheelEvent);
			};

			struct JoystickButtArgs : EventArgs, sf::Event::JoystickButtonEvent {
				CREATE_CONVERSION_CONSTRUCT(JoystickButtArgs, sf::Event::JoystickButtonEvent);
			};

			struct JoystickMoveArgs : EventArgs, sf::Event::JoystickMoveEvent {
				CREATE_CONVERSION_CONSTRUCT(JoystickMoveArgs, sf::Event::JoystickMoveEvent);
				typedef sf::Joystick::Axis Axis;
			};

			struct JoystickArgs : EventArgs, sf::Event::JoystickConnectEvent {
				CREATE_CONVERSION_CONSTRUCT(JoystickArgs, sf::Event::JoystickConnectEvent);
			};

			struct ResizeArgs:EventArgs, sf::Event::SizeEvent{
				CREATE_CONVERSION_CONSTRUCT(ResizeArgs, sf::Event::SizeEvent);
			};

			struct TextTypeArgs :EventArgs, sf::Event::TextEvent {
				CREATE_CONVERSION_CONSTRUCT(TextTypeArgs, sf::Event::TextEvent);
			};
		}
	}
}