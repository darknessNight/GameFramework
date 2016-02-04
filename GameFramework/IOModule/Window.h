#pragma once
#include "../stdafx.h"
#include "SFML\Graphics.hpp"
#include "EventArgs.hpp"

namespace RPGFramework {
	namespace IOModule {
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
			Events::Event<Events::KeyboardArgs> KeyPressed;
			Events::Event<Events::MouseArgs> MouseButtonDown;
#pragma endregion

		protected:
			std::shared_ptr<std::thread> thread;
			sf::RenderWindow window;
		};
	}
}