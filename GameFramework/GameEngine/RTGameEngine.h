#pragma once
#include "Action.h"
#include "GameEngine.h"


namespace GF {
	namespace GameEngine {
		class RTGameEngine : public GameEngine {
		public:
			virtual void start() override;
			virtual void startAsync();
			virtual void stop() override;
			virtual void pause() override;
		public:
			bool play = false;
		};
	}
}