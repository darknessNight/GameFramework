#pragma once
#include "EqType.h"
#include "Equipment.h"
namespace GF {
	namespace GameEngine {
		class EqSlot {
		public:
			virtual bool Equip(Equipment eq);
			virtual void Dequip();
		public:
			EqType type;
			Equipment el;
		};
	}
}