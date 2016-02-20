#include "Map.h"
#ifdef DEBUG
#include "../MemGuard.h"
#endif

void GF::GameEngine::Map::appendEvent(MemGuard<MapEvent> el)
{
	std::lock_guard<std::mutex> guard(mutex);
	events.push_back(el);
}

void GF::GameEngine::Map::removeEvent(MemGuard<MapEvent> el)
{
	std::lock_guard<std::mutex> guard(mutex);
	for (auto i = events.begin(); i != events.end(); i++) {
		if (el == (*i)) {
			std::swap(i,events.end());events.pop_back();
			break;
		}
	}
}

void GF::GameEngine::Map::clearEvents()
{
	std::lock_guard<std::mutex> guard(mutex);
	events.clear();
}
