#pragma once
#include "Control.h"


namespace GF {
	namespace Controller {
		namespace Controls {
			class Label :public Control {
			public:
				using Control::Control;
			protected:
				void render(sf::RenderTarget* target)override;
				virtual void drawText();
			public:
				bool autoSize = true;
			};
		}
	}
}