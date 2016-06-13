#pragma once
#include <vector>
#include <functional>
#include "DialogText.h"

namespace GF {
	namespace GameEngine {
		class Dialog {
		public:
			virtual Core::shared_ptr<Dialog> choice(int no);
		public:
			std::vector<Core::shared_ptr<Dialog>> options;
			std::vector<DialogText> Texts;
			std::string displayedResponse;
		};
	}
}