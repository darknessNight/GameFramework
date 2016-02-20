#include "StaticObject.h"
#include "GameEngine.h"
#ifdef DEBUG
#include "../MemGuard.h"
#endif

void GF::GameEngine::StaticObject::selfDestroy()
{
	onDead();
	engine->removeStaticObject(*this);
}
