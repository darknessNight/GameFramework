#pragma once
#include <functional>
#include "../IOModule/Sound.h"

namespace GF {
	namespace GameEngine {
		class DialogText {
		public:
			virtual void show();
		public:
			IOModule::Sounds::Voice playSound;
			std::string text;
			int timer;
			std::function<void(void)> draw;
		};
	}
}