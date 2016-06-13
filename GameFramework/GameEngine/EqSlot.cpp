#include "EqSlot.h"
#ifdef DEBUG
#include "../MemGuard.h"
#endif

bool GF::GameEngine::EqSlot::Equip(Core::shared_ptr<Equipment> eq)
{
	if (eq->type == type) {
		el = eq;
		return true;
	}
	return false;
}

void GF::GameEngine::EqSlot::Dequip()
{
	el = nullptr;
}

GF::Core::shared_ptr<GF::GameEngine::Equipment> GF::GameEngine::EqSlot::getEq()
{
	return el;
}
