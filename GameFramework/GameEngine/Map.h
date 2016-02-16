#pragma once
#include <vector>
#include "GameMapEvents.h"
#include "Mob.h"
#include "Model.h"
#include "Types.h"

namespace GF {
	namespace GameEngine {
		class Map {

		public:

			virtual bool isMovePosible(Pos from, Pos to, Model model);

			virtual Pos move(Pos from, Pos to, Model model);

			virtual void detectEvent(Pos pos, Mob mob);

		public:
			Pos acceptableRange;
			std::vector< GameMapEvents > events;

		};
	}
}