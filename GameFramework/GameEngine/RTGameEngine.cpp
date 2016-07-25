#include "RTGameEngine.h"
#include "../Core/Exception.h"
#include <chrono>

void GF::GameEngine::RTGameEngine::start()
{
	using namespace std::chrono_literals;
	play = true;
	while (play) {
		while (paused)
			std::this_thread::sleep_for(100ms);
		for each(auto mob in this->mobs) {
			mob->doScript();
		}
		std::this_thread::sleep_for(1ms);
	}
};

void GF::GameEngine::RTGameEngine::startAsync()
{
	throw GF::Core::Exception("Not implement function startAsync in RTGameEngine " __FILE__);
}

void GF::GameEngine::RTGameEngine::stop()
{
	play = false;
}

void GF::GameEngine::RTGameEngine::pause()
{
	paused = !paused;
};
