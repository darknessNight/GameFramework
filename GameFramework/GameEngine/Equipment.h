#pragma once
#include "EqType.h"
#include "Statistics.h"
#include <string>

namespace GF {
	namespace GameEngine {
		class Equipment {
		public:
			std::string name;
			Statistics buffs;
			EqType type;
		};
	}
}