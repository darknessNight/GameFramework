#pragma once
#include <vector>
#include <map>

#include "Action.h"
#include "EqSlot.h"
#include "InteractiveObject.h"
#include "MobGroup.h"
#include "MobState.h"
#include "Skill.h"
#include "MobBag.h"

namespace GF {
	namespace GameEngine {
		class Mob abstract: public InteractiveObject {
			friend GameEngine;
		public:
			virtual bool doScript()=0;

			virtual void addSkill(const Skill&);
			virtual Core::MemGuard<const Statistics> getCurrStats() override;
			virtual MobState getState();
			virtual EqSlot& getSlot(int id);
		public:
			std::function<void(Core::MemGuard<Mob>)> AIScript;
			Core::Events::Event<Core::Events::EventArgs> SkillAdded;
			Core::Events::Event<Core::Events::EventArgs> StateChanged;

			MobGroup mainGroup;
			int	outlierGroup=0;

			Bag bag;
		protected:
			std::map<int, EqSlot> egSlots;

			MobState state;
			Action actualAction;
			std::vector<Skill> skills;

			Statistics statsWithEq;

			int loopRate;
		};
	}
}