#pragma once
#include "Action.h"
namespace GF {
	namespace GameEngine {
		class Skill {
		public:
			Action action;
			int lastUse;
			int reloadTime;
			std::string information;
			std::string name;
		};
	}
}