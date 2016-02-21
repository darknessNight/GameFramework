#pragma once
#include <vector>
#include "Types.h"
#include "Model.h"


namespace GF {
	namespace GameEngine {
		class Model2D : public Model {
		public:
			enum CollideType {
				NonCollide,
				MapCollide,
				AllCollide
			};

			Model2D(Size rect,CollideType type=CollideType::AllCollide);
			Model2D(bool **map, unsigned width, unsigned height);
			~Model2D();
			void setCollideType(CollideType);
			bool setMap(bool **map, unsigned width, unsigned height);
			bool isCollide(bool **sourceMap, Box sourceBox, Pos ownStart = { 0,0 });///<prepared object-map collision
			bool isCollide(const Model*)override;///<prepared for object-obcject collistion
			bool isCollide(const Model*, Vector3D shift)override;///<prepared for object-obcject collistion. shift is relate position of elements
			virtual bool isOnLine(Pos pos, Vector3D vector);
		protected:
			void delMap();
		protected:
			CollideType collType;
			bool** collisionMap=nullptr;
		};
	}
}