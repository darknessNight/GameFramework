#pragma once
#include "Action.h"
#include "Mob.h"


namespace GF {
	namespace GameEngine {
		class TurnMob : public Mob {
		public:
			virtual Action doAction();
			std::function<Action(Core::shared_ptr<Mob>)> AIScript;
		};
	}
}