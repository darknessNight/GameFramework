#pragma once
#include <vector>

#include "Action.h"
#include "AttackEffect.h"
#include "EqSlot.h"
#include "Equipment.h"
#include "GameObject.h"
#include "InteractiveObject.h"
#include "MobGroup.h"
#include "MobState.h"
#include "Skill.h"
#include "Statistics.h"

namespace GF {
	namespace GameEngine {
		class Mob : public InteractiveObject {

		public:
			virtual void obtainEffect(AttackEffect effect);
			virtual void colission(GameObject el);
			virtual bool doScript();
			virtual int getGroup();
		private:
			Statistics stats;
			Statistics statsWithEq;
			MobGroup mainGroup;
			std::function<void(void)> AIScript;
			std::vector< EqSlot > egSlots;
			MobState state;
			Action actualAction;
			std::vector< Equipment > bag;
			std::vector< Skill > skills;
			Core::Events::Event<Core::Events::EventArgs> changed;
		private:
			int loopRate;

		};
	}
}