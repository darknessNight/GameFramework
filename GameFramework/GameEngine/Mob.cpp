#include "Mob.h"


void GF::GameEngine::Mob::addSkill(const Skill &skill)
{
	skills.push_back(skill);
	onSkillAdded();
}

std::vector<GF::GameEngine::Skill> GF::GameEngine::Mob::getSkills()
{
	return skills;
}

GF::GameEngine::MobState GF::GameEngine::Mob::getState()
{
	return state;
}

GF::GameEngine::EqSlot & GF::GameEngine::Mob::getSlot(int id)
{
	auto el=eqSlots.find(id);
	if (el != eqSlots.end())
		return (el->second);
	else throw std::runtime_error("This slot doesn't exists: Returned from: GameEngine::Mob::getSlot");
}

void GF::GameEngine::Mob::updateStats(Core::MemGuard<const Statistics>)
{
	Statistics s = *stats;
	if (!canDestroy) s.HP = 0;
	*stats += s;
	onStatsChanged();
	if (stats->HP == 0 && canDestroy) {
		if(disapperAfterDead)
			selfDestroy();
		else onDead();
	}
}

void GF::GameEngine::Mob::onSkillAdded()
{
	SkillEventArgs args;
	args.skill = *skills.rend();
	SkillAdded(this, args);
}

void GF::GameEngine::Mob::calcCurrStats()
{
	//std::lock_guard<std::mutex> lg(mutex);
	currentStats = stats;
	for each (auto el in effects)
	{
		if (el.temp != nullptr)
			currentStats->updateRel(el.temp);
	}
	for each(auto el in eqSlots) {
		currentStats->updateRel(el.second.getEq()->buffs);
	}
}

std::vector<unsigned char> GF::GameEngine::Mob::serialize()
{
	return std::vector<unsigned char>();
}

bool GF::GameEngine::Mob::deserialize(std::vector<unsigned char>)
{
	return false;
}
