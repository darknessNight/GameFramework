#pragma once
#include "Events.hpp"

namespace GF {
	namespace Core {
		class Timer {
		public:
			~Timer();
			void start();
			void startAsync();
			void stop();
			void setInterval(std::chrono::milliseconds);
			std::chrono::milliseconds getInterval();
		public:
			Events::Event<Events::EventArgs> Tick;
		private:
			const unsigned minimalInteval = 10;
			std::thread thread;
			std::chrono::milliseconds interval = std::chrono::milliseconds(100);
			bool active = false;
			std::chrono::high_resolution_clock::time_point last, now;
		};
	}
}