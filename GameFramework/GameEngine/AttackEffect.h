#pragma once
#include "Statistics.h"
#include <string>

namespace GF {
	namespace GameEngine {
		class AttackEffect {
		public:
			Statistics debuff;
			Statistics buff;
			std::string name;
			int time;
			int repeat;
		};
	}
}