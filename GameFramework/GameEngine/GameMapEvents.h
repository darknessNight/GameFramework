#pragma once
#include <functional>
#include "Types.h"
#include "Mob.h"
#include "MobGroup.h"

namespace GF {
	namespace GameEngine {
		class GameMapEvents {

		public:
			Rect area;
			std::function<void(void)> event;
			Mob forMob;
			MobGroup forGroup;
		};

	}
}