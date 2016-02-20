#include "Button.h"
using namespace GF::Controller::Controls;
using namespace GF::IOModule;

void Button::render(sf::RenderTarget * target) {
	if (ownDraw) {
		Image::render(target);
	}
	else {
		if (visible) {
			if (edited) {
				edited = false;
				
				drawBack();
				drawTexture();
				drawBorder();
				drawText();
				texture.display();
				setTexture(texture.getTexture());

			}
			target->draw(*this, rs);
		}
	}
}
