#pragma once
#include <vector>
#include "MapEvents.h"
#include "Mob.h"
#include "Model.h"
#include "Types.h"

namespace GF {
	namespace GameEngine {
		using GF::Core::shared_ptr;
		class Map {
		public:
			virtual bool isMovePosible(Pos from, Vector3D shift, Model* model)=0;///<check is move posible, but not correct it
			virtual Pos moveResult(Pos from, Vector3D shift, Model* model)=0;///<return corrected position of move with shift
			virtual Size getSize()=0;
			virtual void detectEvent(Core::shared_ptr<Mob> mob)=0;///<detect and execute all events for specified mob
			virtual void appendEvent(shared_ptr<MapEvent>);
			virtual void removeEvent(shared_ptr<MapEvent>);
			virtual void clearEvents();
		public:
			Pos acceptableShiftRange = {0.0f,0.0f,0.0f};
		protected:
			std::mutex mutex;
			std::vector< shared_ptr<MapEvent> > events;

		};
	}
}