#pragma once
#include <vector>
#include "Types.h"
#include "GameObject.h"
#include "InteractiveObject.h"
#include "Map.h"
#include "Mob.h"
#include "StaticObject.h"

namespace GF {
	namespace GameEngine {
		class GameEngine {

		public:

			virtual GameObject whatIsOn(Pos pos);
			virtual Mob scanRect(Rect rect);
			virtual void detectOnLine(Pos start, Vector3D vector);
			virtual void start();
			virtual void stop();
			virtual void pause();
			virtual void addInteractiveObject(InteractiveObject el);
			virtual void addStaticObject(StaticObject el);
			virtual void addMob(Mob el);
		public:
			std::vector<StaticObject*> staticObjects;
			std::vector<InteractiveObject*> interactiveObjects;
			std::vector<Mob> mobs;
			bool paused;
			Map map;
		private:
			int loopRate;
		};
	}
}