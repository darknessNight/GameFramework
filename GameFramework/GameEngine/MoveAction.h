#pragma once
namespace GF {
	namespace GameEngine {
		class MoveAction {
			enum Direct{};
		public:
			bool isJump;
			Pos changePos;
			Direct direct;
		};
	}
}