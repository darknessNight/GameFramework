#pragma once
#include <vector>
#include <map>

#include "Action.h"
#include "EqSlot.h"
#include "InteractiveObject.h"
#include "Skill.h"
#include "MobBag.h"

namespace GF {
	namespace GameEngine {
		class Mob abstract: public InteractiveObject, public Core::ObjectSerialize {
			friend GameEngine;
		public:
			virtual std::vector<unsigned char> serialize() override;
			virtual bool deserialize(std::vector<unsigned char>) override;

			virtual bool doScript()=0;
			virtual void addSkill(const Skill&);
			virtual std::vector<Skill> getSkills();

			virtual Pos move(Vector3D);
			
			virtual MobState getState();
			virtual EqSlot& getSlot(int id);

			virtual void updateStats(Core::shared_ptr<const Statistics>);
		protected:
			virtual void onSkillAdded();
			virtual void calcCurrStats() override;
		public:
			Core::Events::Event<SkillEventArgs> SkillAdded;

			MobGroup mainGroup=MobGroup::Neutral;
			int	outlierGroup=0;

			Bag bag;

			bool disapperAfterDead = true;

			void* additionalAIScriptData;
		protected:
			std::map<int, EqSlot> eqSlots;

			MobState state;
			Action actualAction;
			std::vector<Skill> skills;

			int loopRate;
		};
	}
}