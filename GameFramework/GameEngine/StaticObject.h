#pragma once

#include "GameObject.h"
#include "Statistics.h"

namespace GF {
	namespace GameEngine {
		class StaticObject : public GameObject {
		public:
			Statistics stats;
		};
	}
}