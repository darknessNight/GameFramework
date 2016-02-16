#pragma once
#include "../IOModule/GraphObject.h"
#include <functional>
#include "Action.h"
#include "AttackEffect.h"
#include "AttackType.h"
#include "PlayerAction.h"

namespace GF {
	namespace GameEngine {
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