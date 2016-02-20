#include "Textbox.h"
using namespace GF::IOModule;

void GF::Controller::Controls::Textbox::onGainedFocus(Events::EventArgs &args)
{
	active = true;
	edited = true;
	cursorPos = text.size();
	Control::onGainedFocus(args);
}

void GF::Controller::Controls::Textbox::onLostFocus(Events::EventArgs &args)
{
	active = false;
	edited = true;
	Control::onLostFocus(args);
}

void GF::Controller::Controls::Textbox::onTextType(GF::IOModule::Events::TextTypeArgs &args)
{
	Control::onTextType(args);
	if (args.cancel) return;

	if (args.unicode < 0x01F) return;
	if (text.size() < textMaxLenght) {
		text=text.substr(0,cursorPos) + (wchar_t)args.unicode + text.substr(cursorPos);
		cursorPos++;
	}
	edited = true;
}

void GF::Controller::Controls::Textbox::onKeyPressed(Events::KeyboardArgs &args)
{
	Control::onKeyPressed(args);
	if (args.cancel) return;
	switch (args.code) {
	case Keyboard::End:cursorPos = text.size(); break;
	case Keyboard::Home:cursorPos = 0; break;
	case Keyboard::Return:if (allowNewLine) { text = text.substr(0, cursorPos) + L'\n' + text.substr(cursorPos); cursorPos++; }break;
	case Keyboard::Left:if (cursorPos > 0)cursorPos--; break;
	case Keyboard::Right:if (cursorPos < text.size())cursorPos++; break;
	case Keyboard::BackSpace: if (cursorPos > 0) {
		text = text = text.substr(0, cursorPos - 1) + text.substr(cursorPos);
		cursorPos--;
	}
		break;
	case Keyboard::Delete:if (cursorPos + 1 <= text.size())text = text = text.substr(0, cursorPos) + text.substr(cursorPos + 1); break;
	}
	edited = true;
}

void GF::Controller::Controls::Textbox::render(sf::RenderTarget * target) {
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

void GF::Controller::Controls::Textbox::drawText()
{
	if (active)
		textObj.setColor(actForeColor);
	else textObj.setColor(foreColor);

	std::wstring str = text;
	textObj.setPosition(borderSize * 2, borderSize * 2);

	if (active) {
		str=str.substr(0, cursorPos) + L'|' + str.substr(cursorPos);
		std::wstring tmp = str.substr(0, str.find(L'|'));
		textObj.setString(tmp);
		if(textObj.getGlobalBounds().height > getSize().y-4*borderSize)
			textObj.move(0,-(textObj.getGlobalBounds().height - getSize().y+ 4 * borderSize+font.getLineSpacing(textObj.getCharacterSize())));
		int itmp = tmp.rfind(L'\n');
		if (itmp != std::wstring::npos) {
			tmp = tmp.substr(itmp);
			textObj.setString(tmp);
		}
		if (textObj.getGlobalBounds().width > getSize().x - 4 * borderSize)
			textObj.move(-(textObj.getGlobalBounds().width - getSize().x + font.getLineSpacing(textObj.getCharacterSize())), 0);
	}

	textObj.setString(str);
	texture.draw(textObj);
}
