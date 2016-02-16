#pragma once
#include <functional>
#include "GameObject.h"

namespace GF {
	namespace GameEngine {
		class InteractiveObject : public GameObject{
		public:
			virtual void Interact(Core::Events::EventArgs& type);
		public:
			bool canInteract;
			std::function<void(void)> mobInteract;
			std::string name;
		};
	}
}