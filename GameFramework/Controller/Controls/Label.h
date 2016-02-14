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
			public:
				bool autoSize = true;
			};
		}
	}
}