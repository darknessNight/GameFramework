#pragma once
#include "Equipment.h"
#include "Types.h"
#include <map>

namespace GF {
	namespace GameEngine {
		bool operator<(const Posi& lhs, const Posi& rhs);

		class Bag {
		public:
			virtual void addEq(Core::shared_ptr<Equipment>);
			virtual void removeEq(Core::shared_ptr<Equipment>);
			virtual void removeEq(Posi);
			virtual void move(Posi, Posi);
			virtual void clear();
			virtual Core::shared_ptr<Equipment> getEq(Posi);
		protected:
			Posi maxPos = { 100,100,0};
			std::map<Posi, Core::shared_ptr<Equipment>> items;
		};
	}
}