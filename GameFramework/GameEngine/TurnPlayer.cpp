#include "TurnPlayer.h"

GF::GameEngine::Action GF::GameEngine::TurnPlayer::doAction()
{
	Action ret = *queue.begin();
	queue.pop_front();
	return ret;
}

void GF::GameEngine::TurnPlayer::addAction(Action act)
{
	queue.push_back(act);
}

GF::GameEngine::Action GF::GameEngine::TurnPlayer::getAction(int id)
{
	auto i = queue.begin();
	for (int j = 0; j < id; j++)
		i++;
	return *i;
}

void GF::GameEngine::TurnPlayer::clearAction()
{
	queue.clear();
}

void GF::GameEngine::TurnPlayer::removeAction(int id)
{
	auto i = queue.begin();
	for (int j = 0; j < id; j++)
		i++;
	i = queue.erase(i);
}
