#pragma once
#include "MoveAction.h"
#include "../Core/Types.h"

namespace GF {
	namespace GameEngine {
		class InteractiveObject;
		class Action{
		public:
			bool isAttack;
			bool isMove;
			bool isInteract;
			bool isWaiting;
			MoveAction move;
			Core::MemGuard<InteractiveObject> who;
		};
	}
}