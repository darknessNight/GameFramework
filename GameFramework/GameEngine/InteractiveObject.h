#pragma once
#include <functional>
#include "GameObject.h"
#include "Attack.h"

namespace GF {
	namespace GameEngine {
		class Mob;

		class InteractiveObject : public GameObject{
		public:
			virtual std::vector<unsigned char> serialize()override;
			virtual bool deserialize(std::vector<unsigned char>)override;

			virtual void interact(Core::shared_ptr<Mob>);
			virtual void setName(std::string);
			virtual std::string getName();
			virtual Core::shared_ptr<const Statistics> getCurrStats();
			virtual void obtainEffect(const AttackEffect& effect);
			virtual std::vector<AttackEffect> getCurrEffects();
		protected:
			virtual void selfDestroy() override;
			virtual void calcCurrStats();
			virtual void effectLoop();///<one doing of effect management loop
		public:
			Core::Events::Event <InteractEventArgs> Interact;
			Core::Events::Event <InteractEventArgs> ObtainEffect;

			bool canInteract = false;
			float interactRadius=1;
		protected:
			bool asyncEffLoop = false;
			std::chrono::high_resolution_clock::time_point lastEffLoop;
			Core::shared_ptr<Statistics> currentStats;
			std::vector<AttackEffect> effects;
			std::string name;
		};
	}
}