#pragma once
#include "Mob.h"
#include <thread>


namespace GF {
	namespace GameEngine {
		class RTMob : public Mob {
		public:
			virtual void start();
			virtual void stop();
			virtual void pause();
			virtual void setLoopLimit(int);///<limit for AIScript loop in loop doing for second. -1 is infinity
			virtual bool canMove();///<using in AIScript. return info can do script and delay to framelimit and pause
			virtual bool sendToEngine(Action & action);
		public:
			std::function<void(Core::shared_ptr<Mob>)> AIScript;
			RTState state = RTState::Stoped;
		protected:
			std::chrono::milliseconds loopInterval=std::chrono::milliseconds(0);
			const std::chrono::milliseconds pauseSleep = std::chrono::milliseconds(50);
			std::chrono::high_resolution_clock::time_point last;
			std::thread myThread;
			bool paused;
			bool active;
		};

		typedef RTMob RTPlayer;
	}
}