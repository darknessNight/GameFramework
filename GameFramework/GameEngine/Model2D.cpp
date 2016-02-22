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
	collisionMap = new bool*[height];
	for (unsigned i = 0; i < height; i++) {
		collisionMap[i] = new bool[width];
		memcpy(collisionMap[i], map[i], sizeof(bool)*(width));
	}
	collType = CollideType::MapCollide;
	return true;
}

bool GF::GameEngine::Model2D::isCollide(bool ** sourceMap, Box sB, Pos ownStart)
{
	if (sourceMap == nullptr) return false;
	Box bTmp = sB;
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
					&& collisionMap[static_cast<unsigned>(ownStart.y + i)][static_cast<unsigned>(ownStart.x + j)])
					return true;
			}
		}
	}
	return false;
}

bool GF::GameEngine::Model2D::isCollide(const Model* model)
{
	Model2D* m2d = (Model2D*)model;
	if ((m2d->pos.x > pos.x + size.width || m2d->pos.y>pos.y + size.height || m2d->pos.x + m2d->size.width < pos.x ||
		m2d->pos.y + m2d->size.height < pos.y))return false;

	if (collType == CollideType::AllCollide && ((Model2D*)model)->collType == CollideType::AllCollide)return true;
	Pos rpos;
	rpos.x = m2d->pos.x - pos.x;
	rpos.y = m2d->pos.y - pos.y;
	return isCollide(model, rpos);
}

bool GF::GameEngine::Model2D::isCollide(const Model* model, Vector3D rpos)
{
	Model2D* m2d = (Model2D*)model;
	Box box{ -std::fminf(rpos.x,0),-std::fminf(rpos.y,0),size.width - abs(rpos.x),size.height - abs(rpos.y) };
	Pos p = { std::fmaxf(rpos.x,0),std::fmaxf(rpos.y,0) };

	return m2d->isCollide(collisionMap, box, p);
}

bool GF::GameEngine::Model2D::isOnLine(Pos p, Vector3D vector)
{
	if (collType == CollideType::NonCollide)return false;
	//p1=(vector.y)*(p.x - pos.x) + (-vector.x)*(p.y - pos.y); pos=point to check
	vector = { abs(vector.x),abs(vector.y),abs(vector.z) };

	char pCount = 0, zeroCount = 0;
	{
		float pt[4];
		pt[0] = (vector.y)*(p.x - pos.x) + (-vector.x)*(p.y - pos.y);
		pt[1] = (vector.y)*(p.x - pos.x) + (-vector.x)*(p.y - (pos.y + size.height));
		pt[2] = (vector.y)*(p.x - (pos.x + size.width)) + (-vector.x)*(p.y - pos.y);
		pt[3] = (vector.y)*(p.x - (pos.x + size.width)) + (-vector.x)*(p.y - (pos.y + size.height));
		for (char i = 0; i < 4; i++) {
			if (pt[i] > 0) pCount++;
			if (pt[i] == 0) zeroCount++;
		}
	}
	if (!(pCount == 0 || pCount == 4) || zeroCount!=0) {
		if(collType==CollideType::AllCollide) return true;

		Pos p2 = p + vector;
		if (vector.y == 0) {
			unsigned x = static_cast<unsigned>(p.x - pos.x);
			for (unsigned i = 0; i < size.height; i++)
				if (collisionMap[i][x])return true;
		}
		else if (vector.x == 0){
			unsigned y = static_cast<unsigned>(p.y - pos.y);
			for (unsigned i = 0; i < size.width; i++)
				if (collisionMap[y][i])return true;
		}
		else if (vector.x / vector.y > 1) {//for angle bigger than 45 degres
			float a = vector.x / vector.y;
			float b = p.x - a*p.y;
			float w;
			for (unsigned i = 0; i < size.height; i++) {
				w = (pos.y+i)*a + b;
				if (w<pos.x) continue;
				if (w > pos.x + size.width)break;
				if (collisionMap[i][static_cast<unsigned>(w)])return true;
			}
		}
		else {//for angle smaller than 45 degres
			float a = vector.y / vector.x;
			float b = p.y - a*p.x;
			float w;
			for (unsigned i = 0; i < size.width; i++) {
				w = (pos.x + i)*a + b;
				if (w<pos.y) continue;
				if (w > pos.y + size.height)break;
				if (collisionMap[static_cast<unsigned>(w)][i])return true;
			}
		}
	}
	return false;
}

void GF::GameEngine::Model2D::delMap()
{
	if (collisionMap != nullptr) {
		for (unsigned i = 0; i < size.height; i++) {
			delete[] collisionMap[i];
		}
		delete[] collisionMap;
		collisionMap = nullptr;
	}
}
