#include "Map.h"

void GF::GameEngine::Map::appendEvent(MemGuard<GameMapEvents> el)
{
	std::lock_guard<std::mutex> guard(mutex);
	events.push_back(el);
}

void GF::GameEngine::Map::removeEvent(MemGuard<GameMapEvents> el)
{
	std::lock_guard<std::mutex> guard(mutex);
	for (auto i = events.begin(); i != events.end(); i++) {
		if (el == (*i)) {
			i = events.erase(i);
			break;
		}
	}
}

void GF::GameEngine::Map::clearEvents()
{
	std::lock_guard<std::mutex> guard(mutex);
	events.clear();
}
