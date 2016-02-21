#include "GameEngine.h"
using namespace GF::GameEngine;
using namespace GF;

bool PtrCompare(const Core::MemGuard<GameObject> &lhs, const Core::MemGuard<GameObject> &rhs) {
	return (long long)lhs.getPtr() < (long long)rhs.getPtr();
}

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
		if (!(pos.x<(*i)->getPos().x || pos.y<(*i)->getPos().y || 
			pos.x>(*i)->getPos().x+ (*i)->getSize().width || pos.y>(*i)->getPos().y + (*i)->getSize().height))
			return (*i);
	return nullptr;
}

std::vector<Core::MemGuard<GameObject>> GF::GameEngine::GameEngine::scanRect(Box rect)
{
	Box tmp = rect;
	std::list<Core::MemGuard<GameObject>> r;
	rect.width = fminf(map->getSize().width - rect.x, rect.width);
	rect.height = fminf(map->getSize().height - rect.y, rect.height);
	rect.depth = fminf(map->getSize().depth - rect.z, rect.depth);

	Pos rEnd = { rect.x + rect.width,rect.y + rect.height,rect.z + rect.depth };
	for each(unsigned pos in getSectors(rect))
		for (auto i = sectors[pos].begin(); i != sectors[pos].end(); i++) {
			Pos &lpos = (*i)->getPos(); Size &lsize = (*i)->model->size;
			if (!(lpos.x > rEnd.x || lpos.y > rEnd.y || lpos.z > rEnd.z || lpos.x + lsize.width < rect.x ||
				lpos.y + lsize.height < rect.y || lpos.z + lsize.depth < rect.z))
				r.push_back(*i);
		}
	r.sort(PtrCompare);
	r.unique();
	std::vector<Core::MemGuard<GameObject>> ret;
	for each(auto i in r)
		ret.push_back(i);
	return ret;
}

std::vector<Core::MemGuard<GameObject>> GF::GameEngine::GameEngine::detectOnLine(Pos start, Vector3D vector)
{
	//TODO dodaæ dok³adne ograniczenie liczby sektorów
	std::vector<Core::MemGuard<GameObject>> ret;
	if (start.x < 0 || start.y < 0)return ret;

	Pos s = start, v = vector;

	Box box;
	box.x = (vector.x >= 0 ? start.x: 0);
	box.y = (vector.y >= 0 ? start.y : 0);
	box.z = (vector.z >= 0 ? start.z : 0);
	if (vector.x != 0)
	box.width = (vector.x > 0 ? map->getSize().width-start.x : 1);
	if(vector.y!=0)
	box.height = (vector.y > 0 ? map->getSize().height - start.y : start.y);
	if (vector.z != 0)
	box.depth = (vector.z > 0 ? map->getSize().depth - start.z : start.z);

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
	addToSectors(el);
}

void GF::GameEngine::GameEngine::addStaticObject(Core::MemGuard<StaticObject> el)
{
	staticObjects.push_back(el);
	addToSectors(el);
}

void GF::GameEngine::GameEngine::addMob(Core::MemGuard<Mob> el)
{
	mobs.push_back(el);
	addToSectors(el);
}

void GF::GameEngine::GameEngine::removeInteractiveObject(Core::MemGuard<InteractiveObject> el)
{
	removeFromSectors(el);
	for (auto i = interactiveObjects.begin(); i != interactiveObjects.end(); i++)
		if ((*i) == el) {
			std::swap(i, interactiveObjects.end()); interactiveObjects.pop_back();
			break;
		}
}

void GF::GameEngine::GameEngine::removeStaticObject(Core::MemGuard<StaticObject> el)
{
	removeFromSectors(el);
	for (auto i = staticObjects.begin(); i != staticObjects.end(); i++)
		if ((*i) == el) {
			std::swap(i, staticObjects.end());
			staticObjects.pop_back();
			break;
		}
}

void GF::GameEngine::GameEngine::removeMob(Core::MemGuard<Mob> el)
{
	removeFromSectors(el);
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
	physCountOfSectors = (xSectors == 0 ? 1 : xSectors)*(ySectors == 0 ? 1 : ySectors)*(zSectors == 0 ? 1 : zSectors);
	delete[] sectors;
	sectors = new std::list<Core::MemGuard<GameObject>>[physCountOfSectors];
}

void GF::GameEngine::GameEngine::addToSectors(Core::MemGuard<GameObject> el)
{
	std::vector<unsigned> s = getSectors({ el->getPos(), el->getSize() });
	for each(unsigned i in s)
		sectors[i].push_back(el);
}

void GF::GameEngine::GameEngine::removeFromSectors(Core::MemGuard<GameObject> el)
{
	std::vector<unsigned> s = getSectors({ el->getPos(), el->getSize() });
	for each(unsigned i in s)
		sectors[i].remove(el);
}

std::vector<unsigned> GF::GameEngine::GameEngine::getSectors(Box rect)
{
	Box tmp = rect;
	std::vector<unsigned> ret;
	float xStart = floor(rect.x/ sectSize.width),
		yStart = floor(rect.y/ sectSize.height),
		zStart = floor(rect.z/ sectSize.depth),
		xEnd = floor((rect.width+rect.x)/ sectSize.width ),
		yEnd = floor((rect.height + rect.y)/ sectSize.height),
		zEnd = floor((rect.depth + rect.z)/ sectSize.depth);
	if (sectSize.depth == 0)zEnd = zStart = 0;

	for (unsigned z = zStart; z <= zEnd; z++)
		for (unsigned y = yStart; y <= yEnd; y++)
			for (unsigned x = xStart; x <= xEnd; x++) {
				unsigned pos = z*xSectors*ySectors + y*xSectors + x;
				if(pos<physCountOfSectors)
					ret.push_back(pos);
			}
	return ret;
}

unsigned GF::GameEngine::GameEngine::calcSector(Pos p)
{
	unsigned pos;
	pos = floor(p.x / sectSize.width);
	pos += floor(p.y / sectSize.height) * xSectors;
	pos += floor(p.z / (sectSize.depth != 0 ? sectSize.depth : 1))*xSectors*ySectors;
	if (pos < physCountOfSectors)
		return pos;
	else return 0;
}

void GF::GameEngine::GameEngine::objChangePos(Core::MemGuard<GameObject> obj, Pos pos)
{
	//TODO zoptymalizowaæ 
	std::vector<unsigned> s1 = getSectors({ obj->getPos(),obj->getSize() }),
		s2 = getSectors({ pos,obj->getSize() });
	if (s1 != s2) {
		for each(unsigned i in s1)
			sectors[i].remove(obj);
		for each(unsigned i in s2)
			sectors[i].push_back(obj);
	}

	obj->model->pos = pos;
}

void GF::GameEngine::GameEngine::mobMove(Core::MemGuard<Mob> mob, Vector3D shift)
{
	//TODO detect collision on all move, not only at end
	Pos to = map->moveResult(mob->getPos(), shift, mob->getModel());
	if (to != mob->getPos()) {
		for each(unsigned s in getSectors({to, mob->getSize()}))
		for (auto i = sectors[s].begin(); i != sectors[s].end(); i++) {
			if (*i != mob) {
				if ((*i)->model->isCollide(mob->model.getPtr(), to - (*i)->getPos()))return;
			}
		}
		objChangePos(mob, to);
	}
}
