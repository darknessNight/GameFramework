#include "EqSlot.h"

bool GF::GameEngine::EqSlot::Equip(Core::MemGuard<Equipment> eq)
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

GF::Core::MemGuard<Equipment> GF::GameEngine::EqSlot::getEq()
{
	return el;
}
