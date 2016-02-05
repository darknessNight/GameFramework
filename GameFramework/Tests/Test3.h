#pragma once
#include "../IOModule/Window.h"


namespace Test3Helpers {
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> render;
	int frameCount=0;
	std::shared_ptr<GF::IOModule::Texture2D> texture1;
	typedef std::chrono::duration<double, std::micro> timeDur;
	typedef std::chrono::duration<double, std::milli> timeDur2;
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
		static float t;
		t += 0.05;
		texture1->setPos({ sinf(t)*100+400, cosf(t)*100+300 });
	}
}

std::string Test3() {
	using namespace Test3Helpers;
	GF::IOModule::Window window;
	window.setTitle("Test3");
	texture1=window.GetTexture({ 100,100 }, 1);
	texture1->LoadFromFile("./Image.png");
	texture1->setTransformPoint({ 50,50 });
	texture1->rotate(-90);
	texture1->setVisible(true);
	window.WindowRender += Rotate;
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);
	window.setCursorVisible(false);

	start = std::chrono::high_resolution_clock::now();
	window.Show();
	
	
	return std::string();
}
