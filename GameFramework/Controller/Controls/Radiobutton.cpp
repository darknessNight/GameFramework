#include "Radiobutton.h"
using namespace GF::Controller::Controls;
using namespace GF::IOModule;
using namespace GF;


Core::MemGuard<std::vector<Core::MemGuard<Radiobutton>>>  GF::Controller::Controls::Radiobutton::getGroup()
{
	if (group == nullptr) {
		group = new std::vector<Core::MemGuard<Radiobutton>>;
		group->push_back(*this);
	}
	return group;
}

void GF::Controller::Controls::Radiobutton::addToGroup(Core::MemGuard<std::vector<Core::MemGuard<Radiobutton>>> g)
{
	if (g != nullptr) {
		group = g;
		group->push_back(*this);
	}
}

void GF::Controller::Controls::Radiobutton::removeGroup()
{
	if (group != nullptr) {
		for (auto i = group->begin(); i != group->end(); i++) {
			if ((*i) == this) {
				i = group->erase(i);
				break;
			}
		}
		group = nullptr;
	}
}

void GF::Controller::Controls::Radiobutton::onMousePress(Events::MouseButtonArgs &args)
{
	if (!checked) {
		if (group != nullptr) {
			for (auto i = group->begin(); i != group->end(); i++)
				(*i)->setChecked(false);
		}
		setChecked(true);
	}

	Control::onMousePress(args);
}

void GF::Controller::Controls::Radiobutton::drawField()
{
	const SharedTexture* textTmp = nullptr;
	if (active)
		textTmp = actImgTexture;
	else textTmp = imgTexture;

	Shapes::Circle rect;
	rect.setPosition(0, 0);
	rect.setRadius(getSize().y / 2);
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
		Shapes::Circle val;
		val.setPosition(2 * borderSize, 2 * borderSize);
		val.setRadius({ (getSize().y - 4 * borderSize) / 2 });
		if (active)
			val.setFillColor(actForeColor);
		else val.setFillColor(foreColor);

		texture.draw(val, rs);
	}
}
