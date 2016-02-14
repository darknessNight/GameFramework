#pragma once
#include "Control.h"

namespace GF {
	namespace Controller {
		namespace Controls {
			class Checkbox :public Control {
			public:
				using Control::Control;
				virtual void setChecked(bool check = true);
				bool getChecked();
			protected:
				void onMousePress(Events::MouseButtonArgs&)override;
				void render(sf::RenderTarget* target)override;
				virtual void drawField();
			protected:
				bool checked;
			};
		}
	}
}