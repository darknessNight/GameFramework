#pragma once
#include "Action.h"
#include "GameEngine.h"


namespace GF {
	namespace GameEngine {
		class RTGameEngine : public GameEngine {

		public:

			virtual bool checkActionPosible(Action a);
		};
	}
}