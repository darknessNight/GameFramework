#include "Statistics.h"

void GF::GameEngine::Statistics::operator+=(const Statistics &stat)
{
	HP += stat.HP;
	XP += stat.XP;
	Level += stat.Level;
}

GF::GameEngine::Statistics & GF::GameEngine::Statistics::operator+(const Statistics &stat)
{
	Statistics ret;
	ret.HP = stat.HP+HP;
	ret.XP = stat.XP+XP;
	ret.Level = stat.Level+Level;
}

void GF::GameEngine::Statistics::updateRel(Core::MemGuard<const Statistics> stat)
{
	HP += stat->HP;
	XP += stat->XP;
	Level += stat->Level;
}