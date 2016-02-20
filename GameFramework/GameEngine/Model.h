#pragma once
#include "PhysicAttributes.h"
#include "Types.h"
namespace GF {
	namespace GameEngine {
		class Model{
		public:
			Pos pos;
			virtual bool isCollide(const Model*) = 0;
			virtual bool isCollide(const Model*, Vector3D shift) = 0;

			PhysicAttributes attr;
		};
	}
}