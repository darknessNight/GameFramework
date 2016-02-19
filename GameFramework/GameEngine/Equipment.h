#pragma once
#include "EqType.h"
#include "Statistics.h"
#include <string>

namespace GF {
	namespace GameEngine {
		class Equipment {
		public:
			bool operator==(const Equipment&);
			std::string name;
			Statistics buffs;
			EqType type;
		};
	}
}