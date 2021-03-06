/*Checking Imaging element
*/

#pragma once
#include "../IOModule/Window.h"
#include "../IOModule/Image.h"
#include "../IOModule/MultipleGraph.h"
#include <fstream>
#include "Tests.h"


using namespace std::chrono;
using namespace GF::IOModule;
long long ind = 0;
std::chrono::time_point<std::chrono::steady_clock> started = std::chrono::high_resolution_clock::now();
std::chrono::time_point<std::chrono::steady_clock> start;
std::chrono::time_point<std::chrono::steady_clock> render;
int frameCount = 0;
GF::Core::MemGuard<GF::IOModule::Texture2D> texture1;
GF::Core::MemGuard<GF::IOModule::Texture2D> texture2;
typedef std::chrono::duration<double, std::micro> timeDur;
typedef std::chrono::duration<double, std::milli> timeDur2;
typedef std::chrono::duration<double, std::ratio<1, 1000> > timeDurMove;
MultipleGraph2D multi({ 100, 100 });
steady_clock::time_point now, last = high_resolution_clock::now();
GF::IOModule::Posf pos = { 100,100 };
void ControlImage(GF::IOModule::Events::EventArgs& args) {
	now = high_resolution_clock::now();
	float TIP = duration_cast<milliseconds>(now - last).count() / 2.0;
	last = now;
	if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::Up)) pos.y -= TIP;
	if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::Down))pos.y += TIP;
	if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::Left))pos.x -= TIP;
	if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::Right))pos.x += TIP;
	pos.x = __max(0, pos.x);
	pos.x = __min(800, pos.x);
	pos.y = __max(0, pos.y);
	pos.y = __min(600, pos.y);
	texture1->setPosition(pos);
	if (frameCount >= 100) {
		render = std::chrono::high_resolution_clock::now();
		system("cls");
		std::clog << std::chrono::duration_cast<timeDur>(render - start).count() / 100.0 << " micro sec per frame\n"
			<< 100.0 / std::chrono::duration_cast<timeDur2>(render - start).count() * 1000 << " FPS";
		start = render;
		frameCount = 0;


		multi.setActive(ind++ % 2);
	}
	else frameCount++;
}

void SaveWindow(GF::IOModule::Events::KeyboardArgs& args) {
	using namespace GF::IOModule;
	if (args.code == Keyboard::Escape)
		((Window*)args.sender)->captureToFile("./Tests/Test4Window.png");
}

std::string Test4() {
	using namespace GF::IOModule;
	std::string result;
	try {
		char resp = 0;
		GF::IOModule::Window window;
		window.setTitle("Test4");
		window.KeyPressed += SaveWindow;
		window.KeyPressed += Close;
		window.Render += ControlImage;
		window.setVerticalSyncEnabled(true);
		//window.setCursorVisible(false);
		start = std::chrono::high_resolution_clock::now();
		texture1 = nullptr;
		texture1 = window.CreateTexture({ 100,100 });
		texture1->setVisible(true);
		texture1->setOrigin({ 50,50 });
		texture1->loadFromFile("./Image.png");
		texture1->setPosition(pos);
		texture1->setVisible(true);
		Image img({ 500,500 });
		img.setSmooth(true);
		img.setPosition({ 150, 50 });
		img.setVisible(true);
		window.appendGraphObj(GF::Core::make_ptr(img), 0);
		Shapes::Circle c1, c2;
		c1.setFillColor(Color::Magenta);
		c1.setRadius(100);
		c1.setPosition(50, 50);
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
		txt.setStyle(txt.Italic | txt.Underlined);

		img.draw(rect1);
		img.draw(c1);
		img.draw(c2);
		img.draw(txt);

		GF::Core::MemGuard<Image> img2(window.CreateImage({ 100,100 }, 999)), img3(window.CreateImage({ 100,100 }, 1));
		img2->clear(Color::Magenta);
		img2->setPosition({ 200, 10 });
		img3->clear(Color::Cyan);
		img2->setVisible(true);
		img3->setVisible(true);
		img3->draw(c1);
		img3->setPosition({ 300, 10 });
		multi.append(img3);
		multi.append(img2);
		multi.setActive(0);
		multi.setPosition({ 0,10 });
		window.appendGraphObj(GF::Core::make_ptr(multi), 0);
		try {
			multi.append(GF::Core::make_ptr(img));
		}
		catch (std::exception) {
			std::clog << "Throwed";
		}

		window.Show();


		multi.clear();
		window.clearGraphObjs();

		std::cout << "\nDo you see a moving image(on keys) and one switching box and some others images? (Y/N)\n";
		std::cin >> resp;
		if (resp != 'y' && resp != 'Y') result += "Cannot load texture from memory\n";

		img.SaveToFile("./Tests/Test4Img.png");
	}
	catch (std::exception e) {
		return std::string("Catched exception") + e.what();
	}
	catch (std::exception* e) {
		return std::string("Catched exception") + e->what();
	}
	return result;
}
