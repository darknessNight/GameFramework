#include "StaticObject.h"
#include "GameEngine.h"

void GF::GameEngine::StaticObject::selfDestroy()
{
	onDead();
	engine->removeStaticObject(*this);
}
