#pragma once
#include "Map.h"
#include "Types.h"

namespace GF {
	namespace GameEngine {
		class Map3D : public Map {
			Map3D() { throw NonImplementError("Inside " __FILE__); }
		public:
			Box colisionRectagle;
		};
	}
}