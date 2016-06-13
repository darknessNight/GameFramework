#pragma once
#include <functional>
#include "Action.h"

namespace GF {
	namespace GameEngine {
		enum AttackType {
			Combat,
			Ranged,
			Indirect,
		};

		class AttackEffect {
		public:
			Core::shared_ptr<Statistics> temp;///<temporary effect
			Core::shared_ptr<Statistics> perm;///<permament change of statistics
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
			std::function<void(Pos,Vector3D)> behaviour;///<it behaviour of attack example: create bullet or arrow or magic ball
			std::string name;
			void* additionalData;
		};
	}
}