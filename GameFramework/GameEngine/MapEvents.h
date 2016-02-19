#pragma once
#include <functional>
#include "Types.h"
#include "Mob.h"
#include "MobGroup.h"

namespace GF {
	namespace GameEngine {
		struct MapEventArgs:public Core::Events::EventArgs{
			Core::MemGuard<Mob> mob;
		};
		struct MapEvent{
			Box area;
			Core::Events::Event<MapEventArgs> event;
			Core::MemGuard<Mob> forMob;
			int forGroup;
		};

	}
}