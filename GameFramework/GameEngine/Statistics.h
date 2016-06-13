#pragma once
#include "../Core/Types.h"
namespace GF {
	namespace GameEngine {
		class Statistics {
		public:
			Statistics& operator=(const Statistics&) = default;

			virtual void operator+=(const Statistics&);
			virtual Statistics& operator+(const Statistics&);
			virtual void updateRel(Core::shared_ptr<const Statistics>);
		public:
			int HP;
			int XP;
			int Level;
		};
	}
}