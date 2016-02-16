#pragma once
#include <vector>
#include "Types.h"
#include "Model.h"


namespace GF {
	namespace GameEngine {
		class Model2D : public Model {
		public:
			Rect rectagle;
			bool** colisionMap;
		};
	}
}