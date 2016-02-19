#pragma once
#include <vector>
#include <functional>
#include "DialogText.h"

namespace GF {
	namespace GameEngine {
		class Dialog {
		public:
			virtual Core::MemGuard<Dialog> choice(int no);
		public:
			std::vector<Core::MemGuard<Dialog>> options;
			std::vector<DialogText> Texts;
			std::string displayedResponse;
		};
	}
}