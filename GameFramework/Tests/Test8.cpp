/*
Test obs³ugi w¹tków.
*/

#pragma once
#include "../../GameFramework/IOModule/Window.h"
#include "../../GameFramework/IOModule/Sound.h"

namespace Test8Helpers {
	using namespace std::literals;
	bool bresult = false;
	void func(GF::Core::MemGuard<int> tia) {
		(*tia)++;
	}

	void func2(GF::Core::MemGuard<int> tia) {
		(*tia)--;
		if ((*tia) == 0)bresult = true;
		else bresult = false;
	}

	void DrawM1_1(GF::Core::MemGuard<GF::IOModule::Image> im) {
		using namespace GF::IOModule;
		Shapes::Circle circle;
		circle.setFillColor(Color::Red);
		circle.setRadius(30);
		im->draw(circle);
	}

	void DrawM1_2(GF::Core::MemGuard<GF::IOModule::Image> im) {
		using namespace GF::IOModule;
		std::chrono::seconds m(1);
		std::this_thread::sleep_for(m);
		Shapes::Circle circle;
		circle.setFillColor(Color::Red);
		circle.setRadius(30);
		circle.setPointCount(3);
		circle.setPosition(50, 50);
		im->draw(circle);
	}
}

std::string Test8() {
	std::string result;
	using namespace Test8Helpers;
	using namespace GF;
	using namespace GF::IOModule;
	using namespace GF::Core;
	using namespace std::literals;
	char ret;

	try {
		MemGuard<int> f1;
		f1 = new int;
		(*f1) = 0;

		for (int i = 0; i < 100; i++)
			std::thread(func, f1).detach();

		std::thread th(func, f1);
		if (th.joinable()) th.join();
		if((*f1)!=101) result += "Access to memory failed\n";

		if (true) {
			bresult = false;
			MemGuard<int> f2;
			f2 = new int;
			(*f2) = 100;
			for (int i = 0; i < 100; i++)
				std::thread(func2, f2).detach();
		}

		std::this_thread::sleep_for(5s);
		if(!bresult) result += "Access to memory failed v2\n";

		(*f1) = 0;

		for (int i = 0; i < 50; i++)
			std::thread(func, f1).detach();

		for (int i = 0; i < 50; i++)
			std::thread(func2, f1).detach();

		std::this_thread::sleep_for(5s);
		if ((*f1) != 00) result += "Access to memory failed v3\n";

		Window window;
		window.ShowAsync();
		std::this_thread::sleep_for(1s);
		MemGuard<Texture2D> t1, t2;
		t1 = window.CreateTexture({ 100,100 }, 0);
		t2 = window.CreateTexture({ 100,100 }, 0);
		t1->loadFromFile("./Tests/Resources/Image.png");
		t2->loadFromFile("./Tests/Resources/Image.png");
		t1->setPosition(200, 200);
		t1->setVisible(true);
		std::clog << "\nFirst image\n";
		std::this_thread::sleep_for(2s);
		t2->setVisible(true);
		std::clog << "Second image\n";
		std::this_thread::sleep_for(1s);
		MemGuard<Image> m1;
		m1 = window.CreateImage({ 100,100 }, 0);
		m1->setVisible(true);
		std::clog << "Drawable image\n";
		std::this_thread::sleep_for(1s);
		std::thread thread(DrawM1_1, m1);
		std::thread thread2(DrawM1_2, m1);
		std::this_thread::sleep_for(1s);
		m1->setPosition(300, 300);
		t1->setPosition(100, 500);
		std::this_thread::sleep_for(5s);
		if (thread.joinable())thread.join();
		if (thread2.joinable())thread2.join();

		window.Close();
		std::cout << "Do you see appering images?\n";
		std::cin >> ret;
		if (ret != 'y'&&ret != 'Y') result += "Images doesn't displayed";
	}
	catch (std::exception e) {
		result += "Catched error: " + std::string(e.what());
	}

	return result;
}