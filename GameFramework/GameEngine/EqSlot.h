#pragma once
#include "EqType.h"
#include "Equipment.h"
namespace GF {
	namespace GameEngine {
		class EqSlot {
		public:
			virtual bool Equip(Core::MemGuard<Equipment> eq);
			virtual void Dequip();
			virtual Core::MemGuard<Equipment> getEq();
		protected:
			int type;
			Core::MemGuard<Equipment> el;
		};
	}
}