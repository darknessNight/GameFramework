#pragma once
#include "Mob.h"
#include "PlayerAction.h"
#include "TurnMob.h"

namespace GF {
	namespace GameEngine {
		class TurnPlayer : public TurnMob {

		public:

			virtual void addAction(PlayerAction act);

			virtual void clearAction();
			virtual void removeAction(int i);

		public:
			PlayerAction queue;

		};
	}
}