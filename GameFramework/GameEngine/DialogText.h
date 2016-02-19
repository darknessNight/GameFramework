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
			int time;
			std::function<void(std::string, int time)> draw;
			Core::Events::Event<Core::EventArgs> ShowStart;
			Core::Events::Event<Core::EventArgs> ShowEnd;
		};
	}
}