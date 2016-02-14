#pragma once
#include "Control.h"


namespace GF {
	namespace Controller {
		namespace Controls {
			class Progressbar :public Control {
			public:
				using Control::Control;
				void setCurrent(float);//value between 0 and 100
				float getCurrent();
			protected:
				void render(sf::RenderTarget* target)override;
				virtual void drawValue();
			protected:
				float current = 50.0f;
				const float currentMin = 0.0f;
				const float currentMax = 100.0f;
			};

			class ProgressbarH :public Progressbar {
			public:
				using Progressbar::Progressbar;
			protected:
				void drawValue()override;
			};
		}
	}
}