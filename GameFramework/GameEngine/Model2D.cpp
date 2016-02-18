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
	colisionMap = new bool*[height + 1];
	for (unsigned i = 0; i < height; i++) {
		colisionMap[i] = new bool[width + 1];
		memcpy(colisionMap[i], map[i], sizeof(bool)*(width));
	}
	collType = CollideType::MapCollide;
	return true;
}

bool GF::GameEngine::Model2D::isCollide(bool ** sourceMap, Box sB)
{
	switch (collType) {
	case CollideType::NonCollide:return false; break;
	case CollideType::AllCollide:
		for (unsigned i = 0; i < std::fminf(sB.height,size.height); i++) {
			for (unsigned j = 0; j < std::fminf(sB.width,size.width); j++) {
				if (sourceMap[static_cast<unsigned>(sB.y + i)][static_cast<unsigned>(sB.x + j)]) return true;
			}
		}
		break;
	default:
		for (unsigned i = 0; i < std::fminf(sB.height, size.height); i++) {
			for (unsigned j = 0; j < std::fminf(sB.width, size.width); j++) {
				if (sourceMap[static_cast<unsigned>(sB.y + i)][static_cast<unsigned>(sB.x + j)]
					&& colisionMap[i][j]) return true;
			}
		}
		break;
	}
	return false;
}

bool GF::GameEngine::Model2D::isCollide(const Model2D &, Pos)
{
	if (collType == CollideType::AllCollide)  return true;
	return false;
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
