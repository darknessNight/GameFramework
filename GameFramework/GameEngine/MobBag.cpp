#include "MobBag.h"
#ifdef DEBUG
#include "../MemGuard.h"
#endif
using namespace GF::GameEngine;

bool GF::GameEngine::operator<(const Posi& lhs, const Posi& rhs) {
	if (lhs.z != rhs.z)
		return lhs.z < rhs.z;
	else if (lhs.y != rhs.y)
		return lhs.y < rhs.y;
	else return lhs.x < rhs.x;
}

void GF::GameEngine::Bag::addEq(Core::MemGuard<Equipment> el)
{
	for (int z = 0; z <= maxPos.z;z++)
		for (int y = 0; y <= maxPos.y; y++)
			for (int x = 0; x <= maxPos.y; x++)
				if (items.find({ x,y,z }) == items.end()) {
					items.insert_or_assign({ x,y,z }, el);
				}

	throw GameEngineError("Bag is full!");
}

void GF::GameEngine::Bag::removeEq(Core::MemGuard<Equipment> el)
{
	for (auto i = items.begin(); i != items.end();i++)
		if ((*el) == *(i->second)) {
			i=items.erase(i);
			break;
		}
}

void GF::GameEngine::Bag::removeEq(Posi id)
{
	auto i = items.find(id);
	if (i != items.end()) {
		i = items.erase(i);
	}
}

void GF::GameEngine::Bag::move(Posi id1, Posi id2)
{
	std::map<Posi, Core::MemGuard<Equipment>>::iterator p1, p2;
	p1 = items.find(id1); p2 = items.find(id2);
	if (p1 == items.end())return;
	if (p2 != items.end()) {
		Core::MemGuard<Equipment> tmp = p2->second;
		p2->second = p1->second;
		p1->second = tmp;
	}
	else {
		items.insert_or_assign(id2, p1->second);
		p1 = items.erase(p1);
	}
}

void GF::GameEngine::Bag::clear()
{
	items.clear();
}

GF::Core::MemGuard<GF::GameEngine::Equipment> GF::GameEngine::Bag::getEq(Posi id)
{
	auto i = items.find(id);
	if (i != items.end())
		return i->second;
	else return nullptr;
}