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
			Core::MemGuard<Statistics> buffs;
			int type;///<typ, czyli które czêœæ uzbrojenia to jest
			void* additionalData;
		};
	}
}