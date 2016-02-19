#pragma once
#include "../IOModule/GraphObject.h"
#include <functional>
#include "Action.h"
#include "PlayerAction.h"

namespace GF {
	namespace GameEngine {
		enum AttackType {
			Combat,
			Ranged,
			Indirect,
		};

		class AttackEffect {
		public:
			Core::MemGuard<Statistics> temp;///<temporary effect
			Core::MemGuard<Statistics> perm;///<permament change of statistics
			std::string name;
			long long time;///<time of effect or one repeat in milliseconds
			long long currTime;
			int repeatCount;///<count of repeat apply permanent change
		};

		class Attack : public Action {
		public:
			AttackType type;
			int radius;
			int angle;
			AttackEffect effect;
			std::function<void(void)> behaviour;
			std::string name;
			IOModule::GraphObject2D* graph;
			void* additionalData;
		};
	}
}