#include "TurnMob.h"
#ifdef DEBUG
#include "../MemGuard.h"
#endif

GF::GameEngine::Action GF::GameEngine::TurnMob::doAction()
{
	return AIScript(*this);
}
