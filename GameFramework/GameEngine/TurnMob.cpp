#include "TurnMob.h"

GF::GameEngine::Action GF::GameEngine::TurnMob::doAction()
{
	return AIScript(*this);
}
