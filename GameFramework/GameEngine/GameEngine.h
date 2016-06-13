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


			virtual Core::shared_ptr<GameObject> whatIsOn(Pos pos);
			virtual std::vector<Core::shared_ptr<GameObject>> scanRect(Box rect);
			virtual std::vector<Core::shared_ptr<GameObject>> detectOnLine(Pos start, Vector3D vector);
			virtual void objChangePos(GameObject& obj, Pos pos);
			virtual Pos mobMove(Mob& mob, Vector3D shift);

			virtual void start()=0;
			virtual void stop()=0;
			virtual void pause()=0;

			virtual void appendMap(Core::shared_ptr<Map>);
			virtual void addInteractiveObject(Core::shared_ptr<InteractiveObject> el);
			virtual void addStaticObject(Core::shared_ptr<StaticObject> el);
			virtual void addMob(Core::shared_ptr<Mob> el);

			virtual void removeInteractiveObject(Core::shared_ptr<InteractiveObject> el);
			virtual void removeStaticObject(Core::shared_ptr<StaticObject> el);
			virtual void removeMob(Core::shared_ptr<Mob> el);
			virtual void setCountOfSectors(unsigned);
		protected:
			void calcSectors();///<create sectors and safe data for calcSector; IMPORTANT: not rewrite positions of actual existing objects
			void addToSectors(Core::shared_ptr<GameObject>);
			void removeFromSectors(Core::shared_ptr<GameObject>);
			std::vector<unsigned> getSectors(Box rect);//
			unsigned calcSector(Pos);
		protected:
			std::vector<Core::shared_ptr<StaticObject>> staticObjects;
			std::vector<Core::shared_ptr<InteractiveObject>> interactiveObjects;
			std::vector<Core::shared_ptr<Mob>> mobs;
			Core::shared_ptr<Map> map;
			
			unsigned countOfSectors=10;
			unsigned physCountOfSectors;
			unsigned xSectors=10;
			unsigned ySectors=1;
			unsigned zSectors=1;
			Size sectSize;
			std::list<Core::shared_ptr<GameObject>>* sectors;
			bool paused;
		protected:
			int loopRate;
		};
	}
}