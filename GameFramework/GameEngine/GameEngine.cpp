#include "GameEngine.h"
using namespace GF::GameEngine;
using namespace GF;

GF::GameEngine::GameEngine::GameEngine()
{
	sectors = new std::list<Core::MemGuard<GameObject>>[countOfSectors];
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

Core::MemGuard<GameObject> GF::GameEngine::GameEngine::whatIsOn(Pos pos)
{
	unsigned s = calcSector(pos);
	for (auto i = sectors[s].begin(); i != sectors[s].end(); i++)
		if ((*i)->getPos() == pos)return (*i);
	return nullptr;
}

std::vector<Core::MemGuard<GameObject>> GF::GameEngine::GameEngine::scanRect(Box rect)
{
	std::vector<Core::MemGuard<GameObject>> ret;
	rect.width = fminf(map->getSize().width - rect.x, rect.width);
	rect.height = fminf(map->getSize().height - rect.x, rect.height);
	rect.depth = fminf(map->getSize().depth - rect.x, rect.depth);

	unsigned xStart = floor(sectSize.width / rect.x),
		yStart = floor(sectSize.height / rect.y),
		zStart = floor(sectSize.depth / rect.z),
		xEnd = xStart + ceil(sectSize.width / rect.width),
		yEnd = yStart + ceil(sectSize.height / rect.height),
		zEnd = zStart + ceil(sectSize.depth / rect.depth);
	Pos rEnd = { rect.x + rect.width,rect.y + rect.height,rect.z + rect.depth };
	//TODO to byæ siódmy poziom zag³êbienia. zrobiæ coœ z tym.
	for (unsigned z = zStart; z <= zEnd; z++) 
	for (unsigned y = zStart; y <= zEnd; y++) 
	for (unsigned x = zStart; x <= zEnd; x++) {
		unsigned pos = z*xSectors*ySectors + y*xSectors + x;
		if (pos < countOfSectors)
			for (auto i = sectors[pos].begin(); i != sectors[pos].end(); i++) {
				Pos &lpos = (*i)->getPos(); Size &lsize = (*i)->model->size;
				if(!(lpos.x>rEnd.x || lpos.y>rEnd.y || lpos.z>rEnd.z || lpos.x+lsize.width<rect.x ||
					lpos.y+lsize.height<rect.y || lpos.z+lsize.depth<rect.z))
				ret.push_back(*i);
			}
	}
	return ret;
}

std::vector<Core::MemGuard<GameObject>> GF::GameEngine::GameEngine::detectOnLine(Pos start, Vector3D vector)
{
	//TODO dodaæ dok³adne ograniczenie liczby sektorów
	std::vector<Core::MemGuard<GameObject>> ret;
	if (start.x <= 0 || start.y <= 0)return ret;

	Box box;
	box.x=(vector.x > 0 ? start.x : 0);
	box.y = (vector.y > 0 ? start.y : 0); 
	box.z = (vector.z > 0 ? start.z : 0);
	box.width = (vector.x > 0 ? map->getSize().width - start.x : start.x);
	box.height = (vector.y > 0 ? map->getSize().height - start.y : start.y);
	box.width = (vector.z > 0 ? map->getSize().depth - start.z : start.z);

	std::vector<Core::MemGuard<GameObject>> appro = scanRect(box);
	for (auto i = appro.begin(); i != appro.end(); i++) {
		if ((*i)->model->isOnLine(start, vector)) ret.push_back(*i);
	}
	return ret;
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
	interactiveObjects.push_back(el);
	sectors[calcSector(el->getPos())].push_back(el);
}

void GF::GameEngine::GameEngine::addStaticObject(Core::MemGuard<StaticObject> el)
{
	staticObjects.push_back(el);
	sectors[calcSector(el->getPos())].push_back(el);
}

void GF::GameEngine::GameEngine::addMob(Core::MemGuard<Mob> el)
{
	mobs.push_back(el);
	//sectors[calcSector(el->getPos())].push_back(el);
}

void GF::GameEngine::GameEngine::removeInteractiveObject(Core::MemGuard<InteractiveObject> el)
{
	sectors[calcSector(el->getPos())].remove(el);
	for (auto i = interactiveObjects.begin(); i != interactiveObjects.end(); i++)
		if ((*i) == el) {
			std::swap(i, interactiveObjects.end()); interactiveObjects.pop_back();
			break;
		}
}

void GF::GameEngine::GameEngine::removeStaticObject(Core::MemGuard<StaticObject> el)
{
	sectors[calcSector(el->getPos())].remove(el);
	for (auto i = staticObjects.begin(); i != staticObjects.end(); i++)
		if ((*i) == el) {
			std::swap(i, staticObjects.end());
			staticObjects.pop_back();
			break;
		}
}

void GF::GameEngine::GameEngine::removeMob(Core::MemGuard<Mob> el)
{
	sectors[calcSector(el->getPos())].remove(el);
	for (auto i = mobs.begin(); i != mobs.end(); i++)
		if ((*i) == el) {
			std::swap(i, mobs.end());
			mobs.pop_back();
			break;
		}
}

void GF::GameEngine::GameEngine::setCountOfSectors(unsigned count)
{
	if (count > 0) {
		delete[] sectors;
		sectors = new std::list<Core::MemGuard<GameObject>>[count];
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
	pos = floor(p.x / sectSize.width);
	pos += floor(p.y / sectSize.height) * xSectors;
	pos += floor(p.z / (sectSize.depth != 0 ? sectSize.depth : 1))*xSectors*ySectors;
	if (pos < countOfSectors)
		return pos;
	else return 0;
}

void GF::GameEngine::GameEngine::objChangePos(Core::MemGuard<GameObject> obj, Pos pos)
{
	unsigned s1, s2;
	s1 = calcSector(obj->getPos()); s2 = calcSector(pos);
	if (s1 != s2) {
		std::list<Core::MemGuard<GameObject>>::iterator it;
		for (auto i = sectors[s1].begin(); i != sectors[s1].end(); i++)
			if (*i == obj) {
				it = i;
				break;
			}
		sectors[s2].splice(sectors[s2].end(), sectors[s1], it);
	}
}

void GF::GameEngine::GameEngine::mobMove(Core::MemGuard<Mob> mob, Vector3D shift)
{
	//TODO detect collision on all move, not only at end
	Pos to = map->moveResult(mob->getPos(), shift, mob->getModel());
	if (to != mob->getPos()) {
		unsigned s = calcSector(to);
		for (auto i = sectors[s].begin(); i != sectors[s].end(); i++) {
			if (*i != mob) {
				if ((*i)->model->isCollide(mob->model.getPtr(), to - (*i)->getPos()))return;
			}
		}
		objChangePos(mob, to);
	}
}
