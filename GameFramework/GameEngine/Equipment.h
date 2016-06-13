#pragma once
#include "Statistics.h"
#include <string>

namespace GF {
	namespace GameEngine {
		class Equipment {
		public:
			bool operator==(const Equipment&);
			std::string name;
			Core::shared_ptr<Statistics> buffs;
			int type;///<typ, czyli kt�re cz�� uzbrojenia to jest
			void* additionalData;
		};
	}
}