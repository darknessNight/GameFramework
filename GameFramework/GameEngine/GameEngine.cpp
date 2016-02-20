#include "GameEngine.h"
using namespace GF::GameEngine;
using namespace GF;

GF::GameEngine::GameEngine::GameEngine()
{
	sectors = new std::vector<Core::MemGuard<GameObject>>[countOfSectors];
}

GF::GameEngine::GameEngine::~GameEngine()
{
	delete[] sectors;
}

std::vector<unsigned char> GF::GameEngine::GameEngine::serialize()
{
	return std::vector<unsigned char>();
}

bool GF::GameEngine::GameEngine::deserialize(std::vector<unsigned char>)
{
	return false;
}

GameObject * GF::GameEngine::GameEngine::whatIsOn(Pos pos)
{
	return nullptr;
}

Mob * GF::GameEngine::GameEngine::scanRect(Box rect)
{
	return nullptr;
}

void GF::GameEngine::GameEngine::detectOnLine(Pos start, Vector3D vector)
{
}

void GF::GameEngine::GameEngine::objChangePos(Core::MemGuard<GameObject> obj, Pos pos)
{
}

void GF::GameEngine::GameEngine::mobMove(Core::MemGuard<Mob> mob, Vector3D shift)
{
}

void GF::GameEngine::GameEngine::start()
{
}

void GF::GameEngine::GameEngine::stop()
{
}

void GF::GameEngine::GameEngine::pause()
{
}

void GF::GameEngine::GameEngine::appendMap(Core::MemGuard<Map> newMap)
{
	staticObjects.clear();
	interactiveObjects.clear();
	mobs.clear();
	for (int i = 0; i < countOfSectors; i++)
		sectors[i].clear();
	map = newMap;
	calcSectors();
}

void GF::GameEngine::GameEngine::addInteractiveObject(Core::MemGuard<InteractiveObject> el)
{
}

void GF::GameEngine::GameEngine::addStaticObject(Core::MemGuard<StaticObject> el)
{
}

void GF::GameEngine::GameEngine::addMob(Core::MemGuard<Mob> el)
{
}

void GF::GameEngine::GameEngine::removeInteractiveObject(Core::MemGuard<InteractiveObject> el)
{
}

void GF::GameEngine::GameEngine::removeStaticObject(Core::MemGuard<StaticObject> el)
{
}

void GF::GameEngine::GameEngine::removeMob(Core::MemGuard<Mob> el)
{
}

void GF::GameEngine::GameEngine::setCountOfSectors(unsigned count)
{
	if (count > 0) {
		delete[] sectors;
		sectors = new std::vector<Core::MemGuard<GameObject>>[count];
		countOfSectors = count;
	}
	calcSectors();
}

void GF::GameEngine::GameEngine::calcSectors()
{
	Size mapSize = map->getSize();
	if (mapSize.width <= 0)mapSize.width = 1;
	if (mapSize.height <= 0)mapSize.height = 1;
	if (mapSize.depth <= 0)mapSize.depth = 1;

	double sectV = (mapSize.depth*mapSize.height*mapSize.width) / countOfSectors;
	double sectS = pow((sectV), (1 / 3));
	sectSize.depth = fmin(sectS, map->getSize().depth);
	if (sectSize.depth == 0)sectS = sqrt(sectV);
	if (map->getSize().height < sectS) {
		sectSize.height = map->getSize().height;
		sectSize.width = sectV / (sectSize.depth != 0 ? sectSize.depth : 1) / sectSize.height;
	}
	else if (map->getSize().width < sectS) {
		sectSize.width = map->getSize().width;
		sectSize.height = sectV / (sectSize.depth != 0 ? sectSize.depth : 1) / sectSize.width;
	}
	else {
		sectSize.width = sectSize.height = sectS;
	}

	xSectors = ceil(map->getSize().width / (sectSize.width != 0 ? sectSize.width : 1));
	ySectors = ceil(map->getSize().height / (sectSize.height != 0 ? sectSize.height : 1));
	zSectors = ceil(map->getSize().depth / (sectSize.depth != 0 ? sectSize.depth : 1));
}

unsigned GF::GameEngine::GameEngine::calcSector(Pos p)
{
	Pos p1 = p;
	unsigned pos;
	pos=floor(p.x / sectSize.width);
	pos+=floor(p.y / sectSize.height) * xSectors;
	pos += floor(p.z / (sectSize.depth != 0 ? sectSize.depth : 1))*xSectors*ySectors;
	return pos;
}
