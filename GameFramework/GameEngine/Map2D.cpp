#include "Map2D.h"
#include "Model2D.h"
#ifdef DEBUG
#include "../MemGuard.h"
#endif

GF::GameEngine::Map2D::Map2D(bool ** map, unsigned width, unsigned height)
{
	if (!setMap(map, width, height))
		throw std::exception("Cannot load map");
}

GF::GameEngine::Map2D::~Map2D()
{
	delMap();
}

bool GF::GameEngine::Map2D::setMap(bool ** map, unsigned width, unsigned height)
{
	delMap();
	if (width <= 0 || height <= 0) return false;
	size.width = width;
	size.height = height;
	collisionMap = new bool*[height];
	for (unsigned i = 0; i < height; i++) {
		collisionMap[i] = new bool[width];
		memcpy(collisionMap[i], map[i], sizeof(bool)*(width));
	}
	return true;
}

void GF::GameEngine::Map2D::delMap()
{
	if (collisionMap != nullptr) {
		for (unsigned i = 0; i < size.height; i++) {
			delete[] collisionMap[i];
		}
		delete[] collisionMap;
		collisionMap = nullptr;
	}
}

bool GF::GameEngine::Map2D::isMovePosible(Pos from, Vector3D shiftV, Model* model)
{
	//TODO poprawi� to g�wno, tak aby dzia�a�o dla dowolnej �cie�ki
	Pos to = from + shiftV;
	Model2D* m2d = (Model2D*)(model);
	if (!(to.x >= 0 && to.y >= 0 && to.x + m2d->size.width <= size.width && to.y <= size.height)||
		!(from.x >= 0 && from.y >= 0 && from.x + m2d->size.width <= size.width && from.y <= size.height)) return false;

	float shiftS;
	float current = 0;
	shiftS = fmax(shiftV.x, shiftV.y);

	Box  boxT;
	boxT.width = m2d->size.width;
	boxT.height = m2d->size.height;

	/*while(shiftS > accuracy) {
		shiftS+=accuracy*(signbit(shiftS) ? 1 : -1);

		if(abs(from.x-to.x)>accuracy)
			from.x += accuracy*(signbit(shiftV.x) ? -1 : 1);
		if (abs(from.y - to.y)>accuracy)
			from.y += accuracy*(signbit(shiftV.y) ? -1 : 1);

		boxT.x = round(from.x);
		boxT.y = round(from.y);
		if(m2d->isCollide(collisionMap, boxT)) return false;
	}*/
	while (from != to) {
		shiftS += accuracy*(signbit(shiftS) ? 1 : -1);
		if (abs(from.x - to.x) >= accuracy)
			from.x += accuracy*(signbit(shiftV.x) ? -1 : 1);
		if (abs(from.y - to.y) >= accuracy)
			from.y += accuracy*(signbit(shiftV.y) ? -1 : 1);

		boxT.x = round(from.x);
		boxT.y = round(from.y);

		if (m2d->isCollide(collisionMap, boxT)) return false;
	}

	boxT.x = round(to.x);
	boxT.y = round(to.y);
	//TODO add detect with acceptable shitf range
	return !m2d->isCollide(collisionMap, boxT);
}

GF::GameEngine::Pos GF::GameEngine::Map2D::moveResult(Pos from, Vector3D shiftV, Model * model)
{
	Pos to = from + shiftV;
	Model2D* m2d = (Model2D*)(model);
	if (!(to.x >= 0 && to.y >= 0 && to.x + m2d->size.width <= size.width && to.y <= size.height) ||
		!(from.x >= 0 && from.y >= 0 && from.x + m2d->size.width <= size.width && from.y <= size.height)) return Pos() ;

	float shiftS;
	float current = 0;
	shiftS = fmax(abs(shiftV.x), abs(shiftV.y));

	Box  boxT;
	boxT.width = m2d->size.width;
	boxT.height = m2d->size.height;

	Pos last;
	while (from!=to) {
		last=from;

		shiftS += accuracy*(signbit(shiftS) ? 1 : -1);
		if (abs(from.x - to.x)>=accuracy)
			from.x += accuracy*(signbit(shiftV.x) ? -1 : 1);
		if (abs(from.y - to.y)>=accuracy)
			from.y += accuracy*(signbit(shiftV.y) ? -1 : 1);

		boxT.x = round(from.x);
		boxT.y = round(from.y);

		if (m2d->isCollide(collisionMap, boxT)) return last;
	}

	return to;
}

void GF::GameEngine::Map2D::detectEvent(Core::MemGuard<Mob> mob)
{
	const Model2D *m2d = (Model2D*)mob->getModel();
	Pos pos=mob->getPos();
	Pos posE = { pos.x + m2d->size.width,pos.y + m2d->size.height };

	MapEventArgs args;
	args.mob = mob;
	for (auto i = events.begin(); i != events.end(); i++) {
		Box &box = (*i)->area;
		if (!(pos.x > box.x + box.width || pos.y > box.y + box.height || posE.x < box.x || posE.y < box.y)) {
			if((*i)->forMob==mob || (*i)->forGroup==mob->mainGroup || (*i)->forGroup == mob->outlierGroup)
				(*i)->event(this, args);
		}
	}
}

GF::GameEngine::Size GF::GameEngine::Map2D::getSize()
{
	return{ size.width,size.height,size.depth };
}
