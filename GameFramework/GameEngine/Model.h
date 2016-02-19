#pragma once
#include "PhysicAttributes.h"
#include "Types.h"
namespace GF {
	namespace GameEngine {
		class Model{
		public:
			virtual bool isCollide(const Model*, Pos pos) = 0;

			PhysicAttributes attr;
		};
	}
}