#pragma once
#include "Checkbox.h"

namespace GF {
	namespace Controller {
		namespace Controls {
			class Radiobutton :public Checkbox {
			public:
				using Checkbox::Checkbox;
				Core::MemGuard<std::vector<Core::MemGuard<Radiobutton>>> getGroup();//if doesn't exist create
				void addToGroup(Core::MemGuard<std::vector<Core::MemGuard<Radiobutton>>>);
				void removeGroup();
			protected:
				Core::MemGuard<std::vector<Core::MemGuard<Radiobutton>>> group=nullptr;
				void onMousePress(Events::MouseButtonArgs&)override;
				void drawField()override;
			};
		}
	}
}