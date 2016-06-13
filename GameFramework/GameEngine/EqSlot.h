#pragma once
#include "Equipment.h"
namespace GF {
	namespace GameEngine {
		class EqSlot {
		public:
			virtual bool Equip(Core::shared_ptr<Equipment> eq);
			virtual void Dequip();
			virtual Core::shared_ptr<Equipment> getEq();
		protected:
			int type;
			Core::shared_ptr<Equipment> el;
		};
	}
}