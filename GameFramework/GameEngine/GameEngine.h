#pragma once
#include <vector>
#include "Types.h"
#include "GameObject.h"
#include "InteractiveObject.h"
#include "Map.h"
#include "Mob.h"
#include "StaticObject.h"
#include "Types.h"

namespace GF {
	namespace GameEngine {
		class GameEngine:public Core::ObjectSerialize {

		public:
			virtual GameObject* whatIsOn(Pos pos);
			virtual Mob* scanRect(Box rect);
			virtual void detectOnLine(Pos start, Vector3D vector);
			virtual void start();
			virtual void stop();
			virtual void pause();
			virtual void addInteractiveObject(Core::MemGuard<InteractiveObject> el);
			virtual void addStaticObject(Core::MemGuard<StaticObject> el);
			virtual void addMob(Core::MemGuard<Mob> el);

			virtual void removeInteractiveObject(Core::MemGuard<InteractiveObject> el);
			virtual void removeStaticObject(Core::MemGuard<StaticObject> el);
			virtual void removeMob(Core::MemGuard<Mob> el);

			virtual void objChangePos(Core::MemGuard<GameObject> obj,Pos pos);
			virtual void mobMove(Core::MemGuard<Mob> mob, Vector3D shift);
		protected:
			std::vector<Core::MemGuard<StaticObject>> staticObjects;
			std::vector<Core::MemGuard<InteractiveObject>> interactiveObjects;
			std::vector<Core::MemGuard<Mob>> mobs;
			bool paused;
			Map* map;
		protected:
			int loopRate;
		};
	}
}