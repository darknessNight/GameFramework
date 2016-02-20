#include "GameEngine.h"
using namespace GF::GameEngine;
using namespace GF;

GF::GameEngine::GameEngine::GameEngine()
{
	sectors = new std::vector<Core::MemGuard<GameObject>>[countOfSectors];
}

GF::GameEngine::GameEngine::~GameEngine()
{
	delete sectors;
}

void GF::GameEngine::GameEngine::start()
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

void GF::GameEngine::GameEngine::setCountOfSectors(unsigned count)
{
	if (count > 0) {
		delete sectors;
		sectors = new std::vector<Core::MemGuard<GameObject>>[count];
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

	xSectors = ceil(sectSize.width / (map->getSize().width != 0 ? map->getSize().width : 1));
	ySectors = ceil(sectSize.height / (map->getSize().height != 0 ? map->getSize().height : 1));
	zSectors = ceil(sectSize.depth / (map->getSize().depth != 0 ? map->getSize().depth : 1));
}

unsigned GF::GameEngine::GameEngine::calcSector(Pos p)
{
	unsigned pos;
	pos=ceil(p.x / sectSize.width);
	pos+=ceil(p.y / sectSize.width * xSectors);
	pos += ceil(p.z / (sectSize.depth != 0 ? sectSize.depth : 1)*xSectors*ySectors);
	return pos;
}
