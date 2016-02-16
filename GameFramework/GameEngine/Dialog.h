#pragma once
#include <vector>
#include <functional>
#include "DialogText.h"

namespace GF {
	namespace GameEngine {
		class Dialog {
		public:
			virtual void choise(int no);
		public:
			std::function<void(void)> userChoise;
			std::vector<Dialog*> options;
			std::vector<DialogText> Texts;
		};
	}
}