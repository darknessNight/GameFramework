#pragma
#include <vector>
#include "Map.h"

namespace GF {
	namespace GameEngine {
		class Map2D : public Map {
		public:
			Map2D();
			Map2D(bool **map, unsigned width, unsigned height);
			~Map2D();
			bool setMap(bool **map, unsigned width, unsigned height);
			virtual bool isMovePosible(Pos from, Vector3D shift, Model* model) override;
			virtual Pos moveResult(Pos from, Vector3D shift, Model* model) override;
			virtual void detectEvent(Mob mob) override;
		private:
			void delMap();
		private:
			float accuracy=1.0f;
			unsigned w=0, h=0;
			bool **colisionMap=nullptr;
			Box size;
		};
	}
}