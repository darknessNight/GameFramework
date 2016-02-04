#pragma once
#include "../stdafx.h"
#include "SFML\Graphics.hpp"
#include "EventArgs.hpp"

namespace GameFramework {
	namespace IOModule {
		typedef sf::Mouse Mouse;
		typedef sf::Keyboard Keyboard;
		typedef sf::Joystick Joystick;

		class Window {
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
		private:
			void InputLoop();
		public:
#pragma region Events
			Events::Event<Events::EventArgs> WindowRender;
			Events::Event<Events::EventArgs> Focus;
			Events::Event<Events::EventArgs> LostFocus;
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
			//async events
			Events::Event<Events::EventArgs> FocusAsync;
			Events::Event<Events::EventArgs> LostFocusAsync;
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
#pragma endregion
#pragma region OnEventsProcuderes
			void OnRender();
			void OnKeyPress();
			void OnMouseMove();
			void OnMouseClick();
			void OnJoystick();
#pragma endregion
		protected:
			sf::Event engEvent;
			std::shared_ptr<std::thread> thread;
			sf::RenderWindow window;
		};
	}
}