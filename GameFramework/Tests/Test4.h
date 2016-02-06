#pragma once
#include "../IOModule/Window.h"
#include "../IOModule/Image.h"
#include "../IOModule/MultipleGraph.h"
#include <fstream>
#include "Test3.h"

namespace Test4Helpers {
	using namespace Test3Helpers;
	using namespace std::chrono;
	std::shared_ptr<GF::IOModule::MultipleGraph2D> multi(new GF::IOModule::MultipleGraph2D({ 100, 100 }));
	steady_clock::time_point now, last=high_resolution_clock::now();
	GF::IOModule::Posf pos = { 100,100 };
	void ControlImage(GF::IOModule::Events::EventArgs& args) {
		now = high_resolution_clock::now();
		float TIP = duration_cast<milliseconds>(now - last).count()/2.0;
		last = now;
		if(GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::Up)) pos.y -= TIP;
		if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::Down))pos.y += TIP;
		if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::Left))pos.x -= TIP;
		if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::Right))pos.x += TIP;
		pos.x = __max(0, pos.x);
		pos.x = __min(800, pos.x);
		pos.y = __max(0, pos.y);
		pos.y = __min(600, pos.y);
		Test3Helpers::texture1->setPosition(pos);
		if (frameCount >= 100) {
			render = std::chrono::high_resolution_clock::now();
			system("cls");
			std::clog << std::chrono::duration_cast<timeDur>(render - start).count() / 100.0 << " micro sec per frame\n"
				<< 100.0 / std::chrono::duration_cast<timeDur2>(render - start).count() * 1000<<" FPS";
			start = render;
			frameCount = 0;


			//multi->setActive((int)TIP % 2);
		}
		else frameCount++;
	}

	void SaveWindow(GF::IOModule::Events::KeyboardArgs& args) {
		using namespace GF::IOModule;
		if (args.code == Keyboard::Escape)
			((Window*)args.sender)->captureToFile("./Tests/Test4Window.png");
	}
}

std::string Test4() {
	using namespace GF::IOModule;
	std::string result;
	try {
		char resp = 0;
		using namespace Test3Helpers;
		GF::IOModule::Window window;
		window.setTitle("Test4");
		window.WindowRender += Rotate;
		window.KeyPress += Test4Helpers::SaveWindow;
		window.KeyPress += Close;
		window.WindowRender += Test4Helpers::ControlImage;
		window.setVerticalSyncEnabled(true);
		//window.setCursorVisible(false);
		start = std::chrono::high_resolution_clock::now();
		texture1 = window.CreateTexture({ 100,100 });
		texture1->setVisible(true);
		texture1->setOrigin({ 50,50 });
		texture1->loadFromFile("./Image.png");
		texture1->setPosition(Test4Helpers::pos);
		texture1->setVisible(true);
		std::shared_ptr<Image> img(new Image({ 500,500 }));
		img->setPosition({ 150, 50 });
		img->setVisible(true);
		window.AppendGraphObj(img, 0);
		Shapes::Circle c1, c2;
		c1.setFillColor(Color::Magenta);
		c1.setRadius(100);
		c1.setPosition(200, 200);
		c2.setFillColor(Color::Cyan);
		c2.setRadius(100);
		c2.setPosition(400, 400);
		Shapes::Rectangle rect1({ 500,500 });
		rect1.setFillColor(Color::Blue);

		Font font;
		font.loadFromFile("C:\\Windows\\Fonts\\ARCARTER.ttf");
		Text txt;
		txt.setFont(font);
		txt.setCharacterSize(20);
		txt.setColor(Color::White);
		txt.setPosition({ 100,100 });
		txt.setString("Hello Test4");
		txt.setRotation(20);
		txt.setStyle(txt.Italic|txt.Underlined);

		img->draw(rect1);
		img->draw(c1);
		img->draw(c2);
		img->draw(txt);
		std::shared_ptr<Image> img2(new Image({ 100,100 })),img3(new Image({ 100,100 })), img4(new Image({ 500,500 }));

		using Test4Helpers::multi;
		img2->clear(Color::Magenta);
		img2->setPosition({ 200, 200 });
		img3->clear(Color::Cyan);
		img3->draw(c1);
		img2->setPosition({ 300, 2000 });
		window.AppendGraphObj(img2,1);
		//window.AppendGraphObj(img3);
		//multi->append(img3);
		//multi->append(img2);
		//multi->setActive(0);
		multi->setPosition({ 10,10 });
		//window.AppendGraphObj(multi);

		try {
			multi->append(img4);
			throw new std::exception("MultipleGraph not throw");
		}
		catch (std::exception) {
			std::clog << "Throwed";
		}

		window.Show();

		std::cout << "\nDo you see a moving image? (Y/N)\n";
		std::cin >> resp;
		if (resp != 'y' && resp != 'Y') result += "Cannot load texture from memory\n";

		img->SaveToFile("./Tests/Test4Img.png");
	}
	catch (std::exception e) {
		return std::string("Catched exception") + e.what();
	}
	catch (std::exception* e) {
		return std::string("Catched exception") + e->what();
	}
	return result;
}
