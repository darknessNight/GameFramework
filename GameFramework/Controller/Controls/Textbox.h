#pragma once
#include "Control.h"


namespace GF {
	namespace Controller {
		namespace Controls {
			class Textbox :public Control {
			public:
				using Control::Control;
			protected:
				void onGainedFocus(Events::EventArgs&)override;
				void onLostFocus(Events::EventArgs&)override;
				void onTextType(Events::TextTypeArgs&)override;
				void onKeyPressed(Events::KeyboardArgs&)override;
				void render(sf::RenderTarget* target)override;

				void drawText();
			public:
				bool allowNewLine = false;
				unsigned textMaxLenght = -1;
			protected:
				unsigned cursorPos;
				bool active = false;
			};
		}
	}
}