#pragma once
#include <functional>
#include "Types.h"
#include "Mob.h"

namespace GF {
	namespace GameEngine {
		struct MapEventArgs:public Core::Events::EventArgs{
			Core::shared_ptr<Mob> mob;
		};
		struct MapEvent{
			Box area;
			Core::Events::Event<MapEventArgs> event;
			Core::shared_ptr<Mob> forMob;
			int forGroup;
		};

	}
}