#pragma once
#include "Menu.h"
#include "../GameEngine/GameEngine.h"
#include "../IOModule/Window.h"
#include "../Core/Types.h"

namespace GF {
	namespace Controller {
		class MainController :public Core::Object{
		public:
			virtual void start()=0;
			virtual void stop() = 0;
			virtual bool changeMap(unsigned id) = 0;
		};
	}
}
