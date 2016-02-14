#include "Label.h"

void GF::Controller::Controls::Label::render(sf::RenderTarget * target)
{
	if (ownDraw) {
		Image::render(target);
	}
	else {
		if (edited) {
			edited = false;
			if (autoSize) {
				textObj.setString(text);
				texture.create(textObj.getGlobalBounds().width, textObj.getGlobalBounds().height * 2, 32);
			}
			texture.draw(textObj);

			texture.display();
			setTexture(texture.getTexture());
		}
		target->draw(*this, rs);
	}
}
