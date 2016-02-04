#pragma once
#include "../stdafx.h"
#include "SFML\Graphics.hpp"
#include "EventArgs.hpp"

namespace GameFramework {
	namespace IOModule {
		typedef sf::Mouse Mouse;
		typedef sf::Keyboard Keyboard;
		typedef sf::Joystick Joystick;
		typedef sf::NonCopyable NonCopyable;
		typedef sf::Vector2i Position;
		typedef sf::Vector2u Size;

		class Window :NonCopyable {
		public:
			Window();
			~Window();
			void Show();
			void ShowAsync();
			void Close();
			//std::shared_ptr<GraphObject> CreateGraphObj(Size size, int z-index);
			//std::shared_ptr<Timer> CreateTimer();
			//bool ApplyGraphObj(std::shared_ptr<GraphObject>);
			//bool ApplyTimer(std::shared_ptr<Timer>);
			//properties
			const std::string& getTitle() { return title; }
			const Size& getSize() { return size; }
			const Position& getPosition() { return pos; }
			void setTitle(const std::string title);
			void setSize(const Size size);
			void setPosition(const Position pos);
			void setCursorVisible(bool flag);
			void setVerticalSyncEnabled(bool enabled);
			void setKeyRepeatEnabled(bool enabled);
			void setFramerateLimit(unsigned int limit);
			void setJoystickThreshold(float threshold);
#ifdef DEBUG
			void TestEvents(sf::Event ev);
#endif // DEBUG

		protected:
			void InputLoop();
#pragma region OnEvent Funcs
			void OnWindowRender();
			void OnClose();
			template <typename ArgType> void OnEvent(Events::Event<ArgType> &sync, Events::Event<ArgType>* async, ArgType args);
#pragma endregion
		public:
#pragma region Events
			Events::Event<Events::EventArgs> WindowRender;
			Events::Event<Events::ResizeArgs> WindowResize;
			Events::Event<Events::EventArgs> WindowFocused;
			Events::Event<Events::EventArgs> WindowLostFocus;
			Events::Event<Events::EventArgs> WindowClose;
			Events::Event<Events::KeyboardArgs> KeyPress;
			Events::Event<Events::KeyboardArgs> KeyRelease;
			Events::Event<Events::MouseButtArgs> MouseButtonPress;
			Events::Event<Events::MouseButtArgs> MouseButtonRelease;
			Events::Event<Events::MouseMoveArgs> MouseMove;
			Events::Event<Events::MouseWheelArgs> MouseWheel;
			Events::Event<Events::EventArgs> MouseLeft;
			Events::Event<Events::EventArgs> MouseEnter;
			Events::Event<Events::JoystickButtArgs> JoystickButtonPress;
			Events::Event<Events::JoystickButtArgs> JoystickButtonRelease;
			Events::Event<Events::JoystickMoveArgs> JoystickMove;
			Events::Event<Events::JoystickArgs> JoystickConnect;
			Events::Event<Events::JoystickArgs> JoystickDisconnect;
			Events::Event<Events::TextTypeArgs> TextType;
			//async events
			Events::Event<Events::EventArgs> WindowRenderAsync;
			Events::Event<Events::ResizeArgs> WindowResizeAsync;
			Events::Event<Events::EventArgs> WindowFocusedAsync;
			Events::Event<Events::EventArgs> WindowLostFocusAsync;
			Events::Event<Events::KeyboardArgs> KeyPressAsync;
			Events::Event<Events::KeyboardArgs> KeyReleaseAsync;
			Events::Event<Events::MouseButtArgs> MouseButtonPressAsync;
			Events::Event<Events::MouseButtArgs> MouseButtonReleaseAsync;
			Events::Event<Events::MouseMoveArgs> MouseMoveAsync;
			Events::Event<Events::MouseWheelArgs> MouseWheelAsync;
			Events::Event<Events::EventArgs> MouseLeftAsync;
			Events::Event<Events::EventArgs> MouseEnterAsync;
			Events::Event<Events::JoystickButtArgs> JoystickButtonPressAsync;
			Events::Event<Events::JoystickButtArgs> JoystickButtonReleaseAsync;
			Events::Event<Events::JoystickMoveArgs> JoystickMoveAsync;
			Events::Event<Events::JoystickArgs> JoystickConnectAsync;
			Events::Event<Events::JoystickArgs> JoystickDisconnectAsync;
			Events::Event<Events::TextTypeArgs> TextTypeAsync;
#pragma endregion

			bool fullscreen = false;
			bool canResize = false;
			bool hasCloseButton = true;
			bool hasTitlebar = true;
		protected:
			std::string title = "Window";
			Position pos = { 0,0 };
			Size size = { 800,600 };
			std::shared_ptr<std::thread> thread;
			sf::RenderWindow window;
			//consts
			const Size MIN_SIZE = { 10,10 };
		};


		template<typename ArgType>
		inline void Window::OnEvent(Events::Event<ArgType>& sync, Events::Event<ArgType>* async, ArgType args)
		{
			if (async != nullptr && async->size() > 0) {
				std::thread t(&Events::Event<ArgType>::operator(), async, this, args);
				t.detach();//TODO to niehumanitarne porzucaæ w¹tki. Do naprawy
			}
			sync(this, args);
		}
	}
}