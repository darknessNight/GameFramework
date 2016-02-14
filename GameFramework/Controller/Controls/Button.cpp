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
				if(active)
					clear(actBackColor);
				else clear(backColor);
				if (imgTexture != nullptr) {
					sf::Sprite sp;
					if(active)
						sp.setTexture(*actImgTexture);
					else sp.setTexture(*imgTexture);
					texture.draw(sp);
				}

				Shapes::Rectangle rect;
				rect.setPosition(0, 0);
				rect.setSize(getSize());
				rect.setFillColor(Color::Transparent);
				if(active)
					rect.setOutlineColor(actBorderColor);
				else rect.setOutlineColor(borderColor);
				rect.setOutlineThickness(-borderSize);

				texture.draw(rect);

				if (active)
					textObj.setColor(actForeColor);
				else textObj.setColor(foreColor);
				

				textObj.setPosition(getSize().x / 2 - textObj.getGlobalBounds().width / 2, 
					getSize().y / 2 - textObj.getGlobalBounds().height);

				texture.draw(textObj);
				texture.display();
				setTexture(texture.getTexture());

			}
			target->draw(*this, rs);
		}
	}
}
