#include "Mob.h"

GF::Core::MemGuard<const GF::GameEngine::Statistics> GF::GameEngine::Mob::currentStatistics()
{
	return statsWithEq;
}
