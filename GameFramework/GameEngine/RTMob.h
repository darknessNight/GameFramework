#pragma once
#include "Mob.h"
#include "RTState.h"
#include <thread>


namespace GF {
	namespace GameEngine {
		class RTMob : public Mob {
		public:
			virtual void play();
			virtual void stop();
			virtual void pause();
		public:
			RTState state;
			std::thread myThread;
			bool paused;

		};
	}
}