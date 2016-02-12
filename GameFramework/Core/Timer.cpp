#include "Timer.h"

GF::Core::Timer::~Timer()
{
	stop();
}

void GF::Core::Timer::start()
{
	if (!active) {
		active = true;
		Events::EventArgs stdArgs;
		std::chrono::high_resolution_clock::time_point nextTime=std::chrono::high_resolution_clock::now() + interval;

		while (active) {
			if(std::chrono::high_resolution_clock::now()<nextTime)
				std::this_thread::sleep_for(interval);
			nextTime += interval;
			Tick(this, stdArgs);
		}
	}
}

void GF::Core::Timer::startAsync()
{
	if (!active) {
		thread = std::thread(&Timer::start,this);
	}
}

void GF::Core::Timer::stop()
{
	active = false;
	if (thread.joinable())
		thread.join();
}

void GF::Core::Timer::setInterval(std::chrono::milliseconds ms)
{
	if (ms.count() >= minimalInteval)
		interval = ms;
}

std::chrono::milliseconds GF::Core::Timer::getInterval()
{
	return interval;
}
