#include "Checkbox.h"
using namespace GF::IOModule;

void GF::Controller::Controls::Checkbox::setChecked(bool check)
{
	checked = check;
	edited = true;
}

bool GF::Controller::Controls::Checkbox::getChecked()
{
	return checked;
}

void GF::Controller::Controls::Checkbox::onMousePress(GF::IOModule::Events::MouseButtonArgs &args)
{
	setChecked(!checked);
	Control::onMousePress(args);
}

void GF::Controller::Controls::Checkbox::render(sf::RenderTarget * target)
{
	if (ownDraw) {
		Image::render(target);
	}
	else {
		if (visible) {
			if (edited) {
				edited = false;
				clear(Color::Transparent);

				drawField();

				if (active)
					textObj.setColor(actForeColor);
				else textObj.setColor(foreColor);


				textObj.setPosition(getSize().y + borderSize * 2,
					getSize().y / 2 - textObj.getGlobalBounds().height);

				texture.draw(textObj);
				texture.display();
				setTexture(texture.getTexture());

			}
			target->draw(*this, rs);
		}
	}
}

void GF::Controller::Controls::Checkbox::drawField()
{
	const SharedTexture* textTmp = nullptr;
	if (active)
		textTmp = actImgTexture;
	else textTmp = imgTexture;

	Shapes::Rectangle rect;
	rect.setPosition(0, 0);
	rect.setSize({ getSize().y,getSize().y });
	if (active)
		rect.setFillColor(actBackColor);
	else rect.setFillColor(backColor);
	if (active)
		rect.setOutlineColor(actBorderColor);
	else rect.setOutlineColor(borderColor);
	rect.setOutlineThickness(-borderSize);

	if (textTmp != nullptr) {
		sf::RenderStates rs1 = sf::RenderStates::Default;
		rs1.texture = textTmp;
		texture.draw(rect, rs1);
	}
	else texture.draw(rect);

	if (checked) {
		Shapes::Rectangle val;
		val.setPosition(2 * borderSize, 2 * borderSize);
		val.setSize({ (getSize().y - 4 * borderSize),(getSize().y - 4 * borderSize) });
		if (active)
			val.setFillColor(actForeColor);
		else val.setFillColor(foreColor);

		texture.draw(val,rs);
	}
}
