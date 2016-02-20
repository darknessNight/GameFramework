/*Checking ways of loading textures
*/
#pragma once
#include "../../GameFramework/IOModule/Window.h"
#include <fstream>
#include "Tests.h"

std::string Test3();
AutoAdd AA3(Test3, "IOModule", "Textures loading");

namespace Test3Helpers {
	std::chrono::time_point<std::chrono::steady_clock> started = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> render;
	int frameCount=0;
	GF::Core::MemGuard<GF::IOModule::Texture2D> texture1;
	GF::Core::MemGuard<GF::IOModule::Texture2D> texture2;
	typedef std::chrono::duration<double, std::micro> timeDur;
	typedef std::chrono::duration<double, std::milli> timeDur2;
	typedef std::chrono::duration<double, std::ratio<1, 1000> > timeDurMove;
	void Rotate(GF::IOModule::Events::EventArgs& arg) {
		if (frameCount>=100) {
			render = std::chrono::high_resolution_clock::now();
			system("cls");
			std::clog << std::chrono::duration_cast<timeDur>(render - start).count()/100.0 << "\n"
				<< 100.0/std::chrono::duration_cast<timeDur2>(render - start).count()*1000;
			start = render;
			frameCount = 0;
		}
		else frameCount++;
		float f = std::chrono::duration_cast<timeDurMove>(started - std::chrono::high_resolution_clock::now()).count()/1000;
		texture1->setPosition({ sinf(f)*200+400,
			cosf(f)*200+300 });
	}

	void Close(GF::IOModule::Events::KeyboardArgs &args) {
		if (args.code == GF::IOModule::Keyboard::Escape)
			((GF::IOModule::Window*)args.sender)->Close();
	}
}

std::string Test3() {
	std::string result;
	try {
		char resp = 0;
		using namespace Test3Helpers;
		GF::IOModule::Window window;
		window.setTitle("Test3");
		texture1 = window.CreateTexture({ 100,100 }, 1);
		texture1->setOrigin({ 50,50 });
		texture1->rotate(-45);
		texture1->setVisible(true);
		window.Render += Rotate;
		window.KeyPressed += Close;
		//window.setVerticalSyncEnabled(true);
		window.setCursorVisible(false);
		start = std::chrono::high_resolution_clock::now();


		std::fstream file;
		file.open("./Tests/Resources/Image.png", file.in | file.binary);
		if (file.good()) {
			texture1->loadFromStream(file);
		}
		else return "Test failed test's file not exists";
		file.close();
		window.Show();

		std::cout << "\nDo you see a moving image? (Y/N)\n";
		std::cin >> resp;
		if (resp != 'y' && resp != 'Y') result += "Cannot load texture from stream\n";

		window.removeGraphObj(texture1);
		texture1 = window.CreateTexture({ 100, 100 }, 1);
		texture1->setVisible(true);
		texture1->setOrigin({ 50,50 });

		file.open("./Tests/Resources/Image.png", file.in | file.binary);
		file.seekg(0, file.end);
		unsigned size = file.tellg();
		file.seekg(0, file.beg);
		char* buff = new char[size + 1];
		file.read(buff, size);
		if (file) {
			texture1->loadFromMemory(buff, size);
		}else return "Test failed cannot read test's file";
		file.close();
		delete[] buff;

		window.Show();

		std::cout << "\nDo you see a moving image? (Y/N)\n";
		std::cin >> resp;
		if (resp != 'y' && resp != 'Y') result += "Cannot load texture from memory\n";

		window.removeGraphObj(texture1);
		texture1 = window.CreateTexture({ 100, 100 }, 1);
		texture1->setVisible(true);
		texture1->setOrigin({ 50,50 });
		texture1->loadFromFile("./Tests/Resources/Image.png");
		window.Show();

		std::cout << "\nDo you see a moving image? (Y/N)\n";
		std::cin >> resp;
		if (resp != 'y' && resp != 'Y') result += "Cannot load texture from file\n";

		texture2 = window.CreateTexture({ 100,100 },0);
		texture2->loadFromFile("./Tests/Resources/Image.png");
		texture2->scale({ 3,3 });
		texture2->setPosition({ 250, 150 });
		texture2->setVisible(true);

		texture2 = window.CreateTexture({ 100,100 }, 0);
		texture2->loadFromFile("./Tests/Resources/Image.png");
		texture2->setPosition({ 10, 10 });
		texture2->setVisible(true);
		texture2 = window.CreateTexture({ 100,100 }, 0);
		texture2->loadFromFile("./Tests/Resources/Image.png");
		texture2->setPosition({ 690, 490 });
		texture2->setVisible(true);
		texture2 = window.CreateTexture({ 100,100 }, 0);
		texture2->loadFromFile("./Tests/Resources/Image.png");
		texture2->setPosition({ 740, 60 });
		texture2->setOrigin({ 50,50 });
		texture2->setRotation(-90);
		texture2->setVisible(true);
		texture2 = window.CreateTexture({ 100,100 }, 0);
		texture2->loadFromFile("./Tests/Resources/Image.png");
		texture2->setPosition({ 60, 540 });
		texture2->setOrigin({ 50,50 });
		texture2->setRotation(-90);
		texture2->setVisible(true);
		window.Show();

		std::cout << "\nDo you see a moving image and some static image? (Y/N)\n";
		std::cin >> resp;
		if (resp != 'y' && resp != 'Y') result += "Cannot render two or more images\n";
	}
	catch (std::exception e) {
		return std::string("Catched exception ") + e.what();
	}
	return result;
}
