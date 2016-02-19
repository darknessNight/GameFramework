#pragma once
#include "Types.h"
namespace GF {
	namespace GameEngine {
		class MoveAction {
		public:
			bool isJump;
			Pos changePos;
			float rotation;
		};
	}
}