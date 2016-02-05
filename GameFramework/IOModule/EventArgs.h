#pragma once
#include "../stdafx.h"
#include <list>
#include <SFML\Window.hpp>

namespace GameFramework {
	namespace IOModule {
		namespace Events {
			class Object {};

			template<class ArgType> class Delegate {
			private:
				std::function<void(ArgType&)> func;
				int id;
				void(Object::*primaryFunc)(ArgType&)=nullptr;
			public:
				Delegate(void(f)(ArgType&));
				Delegate(void(Object::*f)(ArgType&),Object* obj);
				Delegate(std::function<void(ArgType&)>, int id);
				Delegate(std::function<void(ArgType&)> , int id, void(Object::*f)(ArgType&));
				Delegate(int id);
				Delegate(int id, void(Object::*)(ArgType&));
				bool operator==(const Delegate& com);
				void operator()(ArgType&);
			};

			static unsigned long long int lastId;
#define CREATE_CONVERSION_CONSTRUCT(NAME, TYPE) NAME(TYPE& ev) {*(TYPE*)this = ev;}
			template<typename ArgType> class Event {//TODO poprawiæ tak, aby nie trzeba przechowywaæ identyfikatora, a zarazem da³o siê u¿ywaæ std::function i std::bind
			public:
				void operator+=(Delegate<ArgType>);
				void operator-=(Delegate<ArgType>);
				void operator()(void*, ArgType&);
				unsigned size();
				void clear();
			private:
				std::list <Delegate<ArgType>> funcs;
			};

			struct EventArgs {
				void* sender;
				int timestamp=0;
				bool cancel=false;
			};

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

			struct ResizeArgs:public EventArgs, public sf::Event::SizeEvent{
				CREATE_CONVERSION_CONSTRUCT(ResizeArgs,sf::Event::SizeEvent);
			};

			struct TextTypeArgs :public EventArgs, public sf::Event::TextEvent {
				CREATE_CONVERSION_CONSTRUCT(TextTypeArgs,sf::Event::TextEvent);
			};
		}
	}
}