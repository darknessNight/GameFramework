#pragma once
#include "../stdafx.h"
#include "SFML\Window.hpp"
#include "EventArgs.hpp"

namespace RPGFramework {
	namespace IOModule {
		class Window {
		public:
			void Show();
			void Close();
			//std::shared_ptr<GraphObject> CreateGraphObj(Size size, int z-index);
			//std::shared_ptr<Timer> CreateTimer();
			//bool ApplyGraphObj(std::shared_ptr<GraphObject>);
			//bool ApplyTimer(std::shared_ptr<Timer>);
		private:
			void InputLoop();
		public:
			Events::Event<Events::KeyboardArgs> KeyPressed;
			Events::Event<Events::MouseArgs> MouseButtonDown;
		};
	}
}