#include "InteractiveObject.h"
#include "Mob.h"
#include "GameEngine.h"

void GF::GameEngine::InteractiveObject::interact(Core::MemGuard<Mob> mob)
{
	if (!canInteract) return;

	int dist = sqrt(pow(mob->getPos().x - pos.x, 2) + pow(mob->getPos().y - pos.y, 2));
	if (dist < interactRadius) return;

	InteractEventArgs args;
	args.mob = mob;
	Interact(this, args);
}

void GF::GameEngine::InteractiveObject::setName(std::string str)
{
	if (str.size()>0)
		name = str;
}

std::string GF::GameEngine::InteractiveObject::getName()
{
	return name;
}

GF::Core::MemGuard<const GF::GameEngine::Statistics> GF::GameEngine::InteractiveObject::getCurrStats()
{
	calcCurrStats();
	return currentStats;
}

void GF::GameEngine::InteractiveObject::obtainEffect(const AttackEffect& effect)
{
	if (effect.perm != nullptr) {
		stats->updateRel(effect.perm);
	}
	if (effect.time > 0) {
		effects.push_back(effect);
		effects.rend()->currTime = effect.time;;
	}
	if (effect.temp != nullptr) {
		calcCurrStats();
	}
}

std::vector<GF::GameEngine::AttackEffect> GF::GameEngine::InteractiveObject::getCurrEffects()
{
	//std::lock_guard<std::mutex> lg(mutex);
	return effects;
}

void GF::GameEngine::InteractiveObject::selfDestroy()
{
	onDead();
	engine->removeInteractiveObject(*this);
}

void GF::GameEngine::InteractiveObject::calcCurrStats()
{
	//std::lock_guard<std::mutex> lg(mutex);
	currentStats = stats;
	for each (auto el in effects)
	{
		if (el.temp != nullptr)
			currentStats->updateRel(el.temp);
	}
}

void GF::GameEngine::InteractiveObject::effectLoop()
{
	//std::lock_guard<std::mutex> lg(mutex);
	do {
		unsigned dur = std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::high_resolution_clock::now() - lastEffLoop).count();
		lastEffLoop = std::chrono::high_resolution_clock::now();
		for (auto i = effects.begin(); i != effects.end();i++)
		{
			auto &el = (*i);
			el.currTime -= dur;
			if (el.currTime <= 0) {
				if (el.repeatCount > 0) {
					el.repeatCount--;
					el.currTime = el.time;
				}
				else {
					i = effects.erase(i);
				}
			}
		}
	} while (asyncEffLoop);
}
