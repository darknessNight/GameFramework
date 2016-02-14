#pragma once
#include "Control.h"


namespace GF {
	namespace Controller {
		namespace Controls {
			class Button :public Control {
			public:
				using Control::Control;
			protected:
				void render(sf::RenderTarget* target)override;
			};
		}
	}
}