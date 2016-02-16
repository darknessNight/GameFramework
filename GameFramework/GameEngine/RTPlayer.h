#pragma once
#include <functional>
#include "RTMob.h"
#include "PlayerAction.h"

namespace GF {
	namespace GameEngine {
		class RTPlayer : public RTMob {
		public:
			virtual bool sendToEngine(PlayerAction& action);
		public:
			std::function<void(void)> control;
		};
	}
}