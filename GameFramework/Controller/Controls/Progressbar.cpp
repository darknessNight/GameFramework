#include "Progressbar.h"

void GF::Controller::Controls::Progressbar::setCurrent(float val)
{
	if (val < currentMin) val = currentMin;
	if(val>currentMax)val=currentMax;
	current = val;
	edited = true;
}

float GF::Controller::Controls::Progressbar::getCurrent()
{
	return current;
}

void GF::Controller::Controls::Progressbar::render(sf::RenderTarget * target)
{
	if (ownDraw) {
		Image::render(target);
	}
	else {
		if (visible) {
			if (edited) {
				edited = false;
				if (active)
					clear(actBackColor);
				else clear(backColor);
				if (imgTexture != nullptr) {
					sf::Sprite sp;
					if (active)
						sp.setTexture(*actImgTexture);
					else sp.setTexture(*imgTexture);
					texture.draw(sp);
				}

				Shapes::Rectangle rect;
				rect.setPosition(0, 0);
				rect.setSize(getSize());
				rect.setFillColor(Color::Transparent);
				if (active)
					rect.setOutlineColor(actBorderColor);
				else rect.setOutlineColor(borderColor);
				rect.setOutlineThickness(-borderSize);
				texture.draw(rect);
				
				drawValue();

				texture.display();
				setTexture(texture.getTexture());

			}
			target->draw(*this, rs);
		}
	}
}

void GF::Controller::Controls::Progressbar::drawValue() {
	Shapes::Rectangle val;
	val.setPosition(2 * borderSize, 2 * borderSize);
	val.setSize({ (getSize().x - 4 * borderSize)*current / 100.0f,(getSize().y - 4 * borderSize) });
	if (active)
		val.setFillColor(actForeColor);
	else val.setFillColor(foreColor);

	texture.draw(val);
}

void GF::Controller::Controls::ProgressbarH::drawValue() {
	Shapes::Rectangle val;
	val.setPosition(2 * borderSize, 2 * borderSize);
	val.setSize({ (getSize().x - 4 * borderSize),(getSize().y - 4 * borderSize)*current / 100.0f });
	if (active)
		val.setFillColor(actForeColor);
	else val.setFillColor(foreColor);

	texture.draw(val);
}
