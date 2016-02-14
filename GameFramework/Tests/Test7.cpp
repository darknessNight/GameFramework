/*Test przekazywania zderzeñ myszy do obiektów
*/
#pragma once
#include "../IOModule/Window.h"
#include "../IOModule/Sound.h"

namespace Test7Helpers {
	using namespace std::chrono;
	GF::Core::MemGuard<GF::IOModule::Texture2D> el, el2;
	GF::IOModule::Posf pos;
	GF::IOModule::Pos wpos;
	steady_clock::time_point now, last = high_resolution_clock::now();

	void MClick(GF::IOModule::Events::MouseButtonArgs& args) {
		GF::IOModule::Texture2D* send = ((GF::IOModule::Texture2D*)args.sender);
		pos.x = args.x;
		pos.y = args.y;
	}

	void MDrag(GF::IOModule::Events::MouseMoveArgs& args) {
		GF::IOModule::Texture2D* send = ((GF::IOModule::Texture2D*)args.sender);
		float dx = args.x - pos.x;
		float dy = args.y - pos.y;
		send->move({ dx,dy });
		pos.x = args.x;
		pos.y = args.y;
	}

	void MWMove(GF::IOModule::Events::EventArgs& args) {
		GF::IOModule::Window* send = ((GF::IOModule::Window*)args.sender);
		wpos = send->getPosition();
		system("cls");
		std::clog << (GF::IOModule::Mouse::getPosition().x - wpos.x) << " " << (GF::IOModule::Mouse::getPosition().y - wpos.y)
			<< "::" << el2->getPosition().x << " " << el2->getPosition().y;
		float dx = (GF::IOModule::Mouse::getPosition().x - wpos.x) - el2->getPosition().x-10;
		float dy = (GF::IOModule::Mouse::getPosition().y - wpos.y) - el2->getPosition().y-10;
		now = high_resolution_clock::now();
		float tip = duration_cast<milliseconds>(now - last).count() / 10.0;
		tip = __min(50, tip);
		last = now;
		float tmp;
		if (dx != 0) {
			tmp = (dx / abs(dx)*tip);
			dx = abs(tmp) > abs(dx) ? dx : tmp;
		}
		if (dy != 0) {
			tmp = (dy / abs(dy)*tip);
			dy = abs(tmp) > abs(dy) ? dy : tmp;
		}

		el2->move({ dx,dy });
	}
}

std::string Test7() {
	std::string result;
	using namespace Test7Helpers;
	using namespace GF;
	using namespace GF::IOModule;
	using namespace GF::Core;
	using namespace std::literals;
	char ret;

	try {
		Window window;
		window.setSize({ 1024,576 });
		window.clickableElements = true;
		window.setTitle("Przesuñ obrazek");
		window.setVerticalSyncEnabled(true);
		window.Render += MWMove;

		MemGuard<Image> m1 = window.CreateImage({ 1024,576 });
		m1->setVisible();
		m1->clear(Color(20,20,20));

		el = window.CreateTexture({ 100, 100 });
		el2 = window.CreateTexture({ 100, 100 });
		if (!el->loadFromFile("./Image.png") || !el2->loadFromFile("./Image.png"))
			throw std::runtime_error("Not laod image");
		el->setColor(Color::Red);
		el->clickable = true;
		el->MousePress += MClick;
		el->MouseMove += MDrag;
		el->setVisible(true);
		el2->setVisible(true);

		el = window.CreateTexture({ 100, 100 });
		if (!el->loadFromFile("./Image.png"))
			throw std::runtime_error("Not laod image");
		el->setColor(Color::Yellow);
		el->clickable = true;
		el->MousePress += MClick;
		el->MouseMove += MDrag;
		el->setVisible(true);

		el = window.CreateTexture({ 100, 100 });
		if (!el->loadFromFile("./Image.png"))
			throw std::runtime_error("Not laod image");
		el->setColor(Color::Blue);
		el->setBlendMode(sf::BlendAdd);
		el->setVisible(true);

		wpos=window.getPosition();
		window.Show();


		std::clog << "\nDo you can move red and yellow picture?(Y/N)\n";
		std::cin >> ret;
		if (ret != 'y'&& ret != 'Y') {
			result += "Mouse event doesn't work";
		}
	}
	catch (std::exception e) {
		result += "Catched error: " + std::string(e.what());
	}

	return result;
}