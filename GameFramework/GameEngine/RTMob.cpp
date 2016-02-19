#include "RTMob.h"
#include "RTGameEngine.h"

void GF::GameEngine::RTMob::start()
{
	if (!active) {
		active = true;
		myThread = std::thread(AIScript, Core::make_ptr(*this));
	}
	paused = false;
	last = std::chrono::high_resolution_clock::now();
}

void GF::GameEngine::RTMob::stop()
{
	active = false;
	if (myThread.joinable())
		myThread.join();
	state = RTState::Stoped;
}

void GF::GameEngine::RTMob::pause()
{
	paused = true;
}

void GF::GameEngine::RTMob::setLoopLimit(int limit)
{
	if (limit > 0 && 1000 / limit>0) {
		loopInterval = std::chrono::milliseconds(1000 / limit);
	}
	else {
		loopInterval = std::chrono::milliseconds(0);
	}
}

bool GF::GameEngine::RTMob::canMove()
{
	if (active) {
		state = RTState::Paused;
		while (paused) {
			std::this_thread::sleep_for(pauseSleep);
		}
		if (loopInterval.count() > 0) {
			state = RTState::Frozen;
			std::chrono::milliseconds dur = std::chrono::duration_cast<std::chrono::milliseconds>(last - std::chrono::high_resolution_clock::now()) + loopInterval;
			if (dur.count() > 0)
				std::this_thread::sleep_for(dur);
		}
		state = RTState::Started;
		last = std::chrono::high_resolution_clock::now();
		return true;
	}
	return false;
}

bool GF::GameEngine::RTMob::sendToEngine(Action & action)
{
	RTGameEngine* ge = dynamic_cast<RTGameEngine*>(engine);
	if (ge != nullptr) return ge->pushAction(action);
	return false;
}