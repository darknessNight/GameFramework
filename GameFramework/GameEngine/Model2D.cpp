#include "Model2D.h"
#ifdef DEBUG
#include "../MemGuard.h"
#endif

GF::GameEngine::Model2D::Model2D(Size s, CollideType type)
{
	size = s;
	collType = type;
}

GF::GameEngine::Model2D::Model2D(bool ** map, unsigned width, unsigned height)
{
	setMap(map, width, height);
}

GF::GameEngine::Model2D::~Model2D()
{
	delMap();
}

void GF::GameEngine::Model2D::setCollideType(CollideType t)
{
	collType = t;
}

bool GF::GameEngine::Model2D::setMap(bool ** map, unsigned width, unsigned height)
{
	delMap();
	if (width <= 0 || height <= 0) return false;
	size.width = width;
	size.height = height;
	colisionMap = new bool*[height];
	for (unsigned i = 0; i < height; i++) {
		colisionMap[i] = new bool[width];
		memcpy(colisionMap[i], map[i], sizeof(bool)*(width));
	}
	collType = CollideType::MapCollide;
	return true;
}

bool GF::GameEngine::Model2D::isCollide(bool ** sourceMap, Box sB, Pos ownStart)
{
	switch (collType) {
	case CollideType::NonCollide:return false;
	case CollideType::AllCollide:
		for (unsigned i = 0; i < std::fminf(sB.height, size.height); i++) {
			for (unsigned j = 0; j < std::fminf(sB.width, size.width); j++) {
				if (sourceMap[static_cast<unsigned>(sB.y + i)][static_cast<unsigned>(sB.x + j)]) 
					return true;
			}
		}
	default:
		for (unsigned i = 0; i < std::fminf(sB.height, size.height); i++) {
			for (unsigned j = 0; j < std::fminf(sB.width, size.width); j++) {
				if (sourceMap[static_cast<unsigned>(sB.y + i)][static_cast<unsigned>(sB.x + j)]
					&& colisionMap[static_cast<unsigned>(ownStart.y+i)][static_cast<unsigned>(ownStart.x+j)]) 
					return true;
			}
		}
	}
	return false;
}

bool GF::GameEngine::Model2D::isCollide(const Model* model)
{
	Model2D* m2d = (Model2D*)model;
	if ((m2d->pos.x > pos.x + size.width || m2d->pos.y>pos.y + size.height || m2d->pos.x+m2d->size.width<pos.x ||
		m2d->pos.y+m2d->size.height<pos.y))return false;

	Pos rpos;
	rpos.x = m2d->pos.x - pos.x;
	rpos.y = m2d->pos.y - pos.y;
	return isCollide(model, rpos);
}

bool GF::GameEngine::Model2D::isCollide(const Model* model, Vector3D rpos )
{
	Model2D* m2d = (Model2D*)model;
	Box box{ -std::fminf(rpos.x,0),-std::fminf(rpos.y,0),size.width - abs(rpos.x),size.height - abs(rpos.y) };
	Pos p = { std::fmaxf(rpos.x,0),std::fmaxf(rpos.y,0) };

	return m2d->isCollide(colisionMap, box, p);
}

void GF::GameEngine::Model2D::delMap()
{
	if (colisionMap != nullptr) {
		for (unsigned i = 0; i < size.height; i++) {
			delete[] colisionMap[i];
		}
		delete[] colisionMap;
		colisionMap = nullptr;
	}
}
