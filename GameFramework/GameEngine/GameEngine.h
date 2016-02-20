/*TODO napisaæ to po angolasku
Silnik w celach usprawnienia sprawdzania kolizji, przechowuje
*/
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
		class GameEngine:public Core::ObjectSerialize {

		public:
			GameEngine();
			~GameEngine();
			std::vector<unsigned char> serialize()override;
			bool deserialize(std::vector<unsigned char>)override;


			virtual Core::MemGuard<GameObject> whatIsOn(Pos pos);
			virtual std::vector<Core::MemGuard<GameObject>> scanRect(Box rect);
			virtual std::vector<Core::MemGuard<GameObject>> detectOnLine(Pos start, Vector3D vector);
			virtual void objChangePos(Core::MemGuard<GameObject> obj, Pos pos);
			virtual void mobMove(Core::MemGuard<Mob> mob, Vector3D shift);

			virtual void start()=0;
			virtual void stop()=0;
			virtual void pause()=0;

			virtual void appendMap(Core::MemGuard<Map>);
			virtual void addInteractiveObject(Core::MemGuard<InteractiveObject> el);
			virtual void addStaticObject(Core::MemGuard<StaticObject> el);
			virtual void addMob(Core::MemGuard<Mob> el);

			virtual void removeInteractiveObject(Core::MemGuard<InteractiveObject> el);
			virtual void removeStaticObject(Core::MemGuard<StaticObject> el);
			virtual void removeMob(Core::MemGuard<Mob> el);
			virtual void setCountOfSectors(unsigned);
		protected:
			virtual void calcSectors();///<create sectors and safe data for calcSector; IMPORTANT: not rewrite positions of actual existing objects
			virtual unsigned calcSector(Pos);//
		protected:
			std::vector<Core::MemGuard<StaticObject>> staticObjects;
			std::vector<Core::MemGuard<InteractiveObject>> interactiveObjects;
			std::vector<Core::MemGuard<Mob>> mobs;
			Core::MemGuard<Map> map;
			
			unsigned countOfSectors=10;
			unsigned xSectors=10;
			unsigned ySectors=1;
			unsigned zSectors=1;
			Size sectSize;
			std::list<Core::MemGuard<GameObject>>* sectors;
			bool paused;
		protected:
			int loopRate;
		};
	}
}