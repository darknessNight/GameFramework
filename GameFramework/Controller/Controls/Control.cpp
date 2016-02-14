#include "Control.h"
using namespace GF::Controller::Controls;
using namespace GF::IOModule;

class AutomaticLoader {
public:
	AutomaticLoader() {
		if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) throw std::runtime_error("Cannot load default font for controls");
	}
	Font font;
}AL;



Font Control::defaultFont=AL.font;

Control::Control(Size size) :Image(size)
{
	caThreshold = -1;
	font = defaultFont;
	setFontSize(defaultTextSize);
	textObj.setFont(font);
	textObj.setColor(foreColor);
	clickable = true;
	actBackColor = backColor;
	actForeColor = foreColor;
	actBorderColor = borderColor;
}

Control::Control(unsigned x, unsigned y) :Control(Size({ x,y }))
{
}

std::wstring GF::Controller::Controls::Control::getText()
{
	return text;
}

void GF::Controller::Controls::Control::setText(std::wstring t)
{
	text = t;
	textObj.setString(t);
	edited = true;
}

void GF::Controller::Controls::Control::setFont(Font & f)
{
	font = f;
	textObj.setFont(font);
	edited = true;
}

Font GF::Controller::Controls::Control::getFont()
{
	return font;
}

void GF::Controller::Controls::Control::setBackColor(Color c)
{
	backColor = c;
	edited = true;
}

Color GF::Controller::Controls::Control::getBackColor()
{
	return backColor;
}

void GF::Controller::Controls::Control::setForeColor(Color c)
{
	foreColor = c;
	textObj.setColor(c);
	edited = true;
}

Color GF::Controller::Controls::Control::getForeColor(Color)
{
	return foreColor;
}

void GF::Controller::Controls::Control::setBorderColor(Color c)
{
	borderColor = c;
	edited = true;
}

Color GF::Controller::Controls::Control::getBordeColor(Color)
{
	return borderColor;
}

void GF::Controller::Controls::Control::setBackTexture(const SharedTexture &texture)
{
	if (actImgTexture == nullptr || actImgTexture == imgTexture)
		actImgTexture = &texture;
	imgTexture = &texture;
	edited = true;
}

void GF::Controller::Controls::Control::setBackTexture(Texture2D &texture)
{
	setBackTexture(texture.getTexture());
}

void GF::Controller::Controls::Control::setActiveBackTexture(const SharedTexture & texture)
{
	actImgTexture = &texture;
	edited = true;
}

void GF::Controller::Controls::Control::setActiveBackTexture(Texture2D &texture)
{
	setActiveBackTexture(texture.getTexture());
}

void GF::Controller::Controls::Control::setOwnDraw(bool enable)
{
	ownDraw = enable;
}

void GF::Controller::Controls::Control::setFontSize(unsigned size)
{
	textObj.setCharacterSize(size);
}

void GF::Controller::Controls::Control::setActiveBackColor(Color c)
{
	actBackColor = c;
	edited = true;
}

void GF::Controller::Controls::Control::setActiveForeColor(Color c)
{
	actForeColor = c;
	edited = true;
}

void GF::Controller::Controls::Control::setActiveBorderColor(Color c)
{
	actBorderColor = c;
	edited = true;
}

Color GF::Controller::Controls::Control::getActiveBackColor()
{
	return actBackColor;
}

Color GF::Controller::Controls::Control::getActiveForeColor()
{
	return actForeColor;
}

Color GF::Controller::Controls::Control::getActiveBorderColor()
{
	return actBorderColor;
}

void GF::Controller::Controls::Control::setBorderSize(float s)
{
	borderSize = s;
	edited = true;
}

float GF::Controller::Controls::Control::getBorderSize()
{
	return borderSize;
}

void GF::Controller::Controls::Control::onMousePress(Events::MouseButtonArgs & args)
{
	active = true;
	edited = true;
	GraphObject2D::onMousePress(args);
}

void GF::Controller::Controls::Control::onMouseRelease(Events::MouseButtonArgs & args)
{
	active = false;
	edited = true;
	GraphObject2D::onMouseRelease(args);
}
