#pragma
#include <vector>
#include "Map.h"

namespace GF {
	namespace GameEngine {
		class Map2D : public Map {
		public:
			Map2D()=default;
			Map2D(bool **map, unsigned width, unsigned height);
			Map2D(unsigned width, unsigned height);
			~Map2D();
			bool setMap(bool **map, unsigned width, unsigned height);
			virtual bool isMovePosible(Pos from, Vector3D shift, Model* model) override;
			virtual Pos moveResult(Pos from, Vector3D shift, Model* model) override;
			virtual void detectEvent(Core::shared_ptr<Mob> mob) override;
			virtual Size getSize()override;
			virtual void setNonCollision(bool nonCollision);
		protected:
			void delMap();
		protected:
			float accuracy=1.0f;
			bool nonCollision = true;
			bool **collisionMap=nullptr;
			Box size;
		};
	}
}