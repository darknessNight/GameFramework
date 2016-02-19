#pragma once
#include "Mob.h"
#include "TurnMob.h"

namespace GF {
	namespace GameEngine {
		class TurnPlayer : public TurnMob {

		public:
			virtual Action doAction()override;
			virtual void addAction(Action act);
			virtual Action getAction(int id);
			virtual void clearAction();
			virtual void removeAction(int i);

		protected:
			std::list<Action> queue;
		};
	}
}