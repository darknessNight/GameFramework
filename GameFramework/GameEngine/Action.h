#pragma once
#include "InteractiveObject.h"
#include "MoveAction.h"

namespace GF {
	namespace GameEngine {
		class Action{
		public:
			bool isAttack;
			bool isMove;
			bool isInteract;
			bool isWaiting;
			MoveAction move;
			InteractiveObject who;

		};
	}
}