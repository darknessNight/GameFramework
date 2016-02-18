#include "Model2D.h"

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

bool GF::GameEngine::Model2D::isCollide(const Model* model, Pos pos)
{
	Model2D* m2d = (Model2D*)model;
	Box box{ -std::fminf(pos.x,0),-std::fminf(pos.y,0),size.width - abs(pos.x),size.height - abs(pos.y) };
	Pos p = { std::fmaxf(pos.x,0),std::fmaxf(pos.y,0) };

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
