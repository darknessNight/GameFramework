#include "Skill.h"

bool GF::GameEngine::Skill::canUse()
{
	return (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - lastUse).count()>reloadTime);
}

void GF::GameEngine::Skill::use()
{
	if (canUse()) {
		lastUse = std::chrono::high_resolution_clock::now();
		Core::EventArgs args;
		Use(this, args);
	}
}
