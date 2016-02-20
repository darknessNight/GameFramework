#include "GameObject.h"
#include "GameEngine.h"
#ifdef DEBUG
#include "../MemGuard.h"
#endif

using namespace GF::GameEngine;

GF::GameEngine::GameObject::GameObject()
{
	init();
}

void GF::GameEngine::GameObject::setPos(Pos pos)
{
	engine->objChangePos(this, pos);
}

Pos GF::GameEngine::GameObject::getPos()
{
	return model->pos;
}

void GF::GameEngine::GameObject::setModel(Core::MemGuard<Model> m)
{
	if (m == nullptr) throw std::runtime_error("Nullptr exception in GameObject");
	model = m;
}

void GF::GameEngine::GameObject::updateStats(Core::MemGuard<const Statistics> stat)
{
	Statistics s = *stats;
	if (!canDestroy) s.HP = 0;
	*stats += s;
	onStatsChanged();
	if (stats->HP == 0 && canDestroy) {
		selfDestroy();
	}
}

Model * GF::GameEngine::GameObject::getModel()
{
	return model.getPtr();
}

void GF::GameEngine::GameObject::setStats(Core::MemGuard<Statistics> stat)
{
	if (stats == nullptr)
		stats = new Statistics;
	*stats = *stat;
}

GF::Core::MemGuard<const Statistics> GF::GameEngine::GameObject::getStats()
{
	return stats;
}

void GF::GameEngine::GameObject::onPosChagned()
{
	Core::EventArgs stdArgs;
	PosChanged(this, stdArgs);
}

void GF::GameEngine::GameObject::onStatsChanged()
{
	Core::EventArgs stdArgs;
	StatsChanged(this, stdArgs);
}

void GF::GameEngine::GameObject::onDead()
{
	Core::EventArgs stdArgs;
	Dead(this, stdArgs);
}
