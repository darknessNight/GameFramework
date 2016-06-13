#pragma once
#include "Checkbox.h"

namespace GF {
	namespace Controller {
		namespace Controls {
			class Radiobutton :public Checkbox {
			public:
				using Checkbox::Checkbox;
				Core::shared_ptr<std::vector<Core::shared_ptr<Radiobutton>>> getGroup();//if doesn't exist create
				void addToGroup(Core::shared_ptr<std::vector<Core::shared_ptr<Radiobutton>>>);
				void removeGroup();
			protected:
				Core::shared_ptr<std::vector<Core::shared_ptr<Radiobutton>>> group=nullptr;
				void onMousePress(Events::MouseButtonArgs&)override;
				void drawField()override;
			};
		}
	}
}