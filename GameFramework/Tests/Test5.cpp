/* Checking cameras and crop images
*/
#pragma once
#include "../IOModule/Window.h"
#include "../IOModule/Image.h"
#include "../IOModule/MultipleGraph.h"
#include "../IOModule/Sound.h"
#include <fstream>

namespace Test5Helpers {
	using namespace std::chrono;
	using namespace GF::IOModule;
	Camera cam1,cam2;
	GF::Core::MemGuard<Image> img1, img2;
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

	steady_clock::time_point now, last = high_resolution_clock::now();
	GF::IOModule::Posf pos = { 0,0 }, pos2 = { 0,0 };
	void ControlImage(GF::IOModule::Events::EventArgs& args) {
		now = high_resolution_clock::now();
		float TIP = duration_cast<milliseconds>(now - last).count() / 2.0f;
		last = now;
		if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::W)) pos.y -= TIP;
		if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::S))pos.y += TIP;
		if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::A))pos.x -= TIP;
		if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::D))pos.x += TIP;

		if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::Up)) pos2.y -= TIP;
		if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::Down))pos2.y += TIP;
		if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::Left))pos2.x -= TIP;
		if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::Right))pos2.x += TIP;

		pos.x = __max(0, pos.x);
		pos.x = __min(1280, pos.x);
		pos.y = __max(0, pos.y);
		pos.y = __min(1024, pos.y);

		pos2.x = __max(0, pos2.x);
		pos2.x = __min(1280, pos2.x);
		pos2.y = __max(0, pos2.y);
		pos2.y = __min(1024, pos2.y);

		cam1.setCenter(pos);
		cam2.setCenter(pos2);
		img1->setPosition(pos);
		img2->setPosition(pos2);

		if (frameCount >= 100) {
			render = std::chrono::high_resolution_clock::now();
			system("cls");
			std::clog << std::chrono::duration_cast<timeDur>(render - start).count() / 100.0 << " micro sec per frame\n"
				<< 100.0 / std::chrono::duration_cast<timeDur2>(render - start).count() * 1000 << " FPS";
			start = render;
			frameCount = 0;
		}
		else frameCount++;
	}

	void SaveWindow(GF::IOModule::Events::KeyboardArgs& args) {
		using namespace GF::IOModule;
		if (args.code == Keyboard::Escape)
			((Window*)args.sender)->captureToFile("./Tests/Test4Window.png");
	}

	void Close(GF::IOModule::Events::KeyboardArgs &args) {
		if (args.code == GF::IOModule::Keyboard::Escape)
			((GF::IOModule::Window*)args.sender)->Close();
	}
}

std::string Test5() {
	using namespace GF::IOModule;
	std::string result;
	try {
		using namespace Test5Helpers;
		char resp = 0;
		GF::IOModule::Window window;
		window.setTitle("Test5");
		window.KeyPressed += SaveWindow;
		window.KeyPressed += Close;
		window.Render += ControlImage;
		window.setVerticalSyncEnabled(true);
		start = std::chrono::high_resolution_clock::now();

		texture1 = window.CreateTexture({ 1280,1024 });
		GF::Core::MemGuard<Texture2D> tmp = window.CreateTexture({ 1280,1024 });
		texture1->setVisible(true);
		texture1->setOrigin({ 50,50 });
		if(!texture1->loadFromFile("./Tests/Resources/img2.jpg"))
		throw std::runtime_error("Cannot read image from file");
		texture1->setPosition(pos);
		texture1->setVisible(true);

		cam1.setSize({ 600,900 });
		cam1.setViewport({ 0,0,0.49f,1 });
		cam2.setSize({ 600,900 });
		cam2.setViewport({ 0.51f,0,0.5f,1 });

		window.appendCamera(cam2);
		window.appendCamera(cam1);

		img1 = window.CreateImage({ 192,256 },99);
		img2 = window.CreateImage({ 128,192 },99);

		MultipleGraph2D multi({ 192,256 });
		Camera pm1({0,8+2*64, 48,60 }), pm2({ 0,0, 36,48 });
		img1->setScale({ 0.75f,0.75f });
		img1->setOrigin({ 24,24 });
		img2->setOrigin({ 24,24 });
		img1->appendCamera(pm1);
		img2->appendCamera(pm2);
		img1->setSmooth(true);
		img2->setSmooth(true);
		if (!img1->loadFromFile("./Tests/Resources/alex.png"))
			throw std::runtime_error("Cannot read image from file");
		if(!img2->loadFromFile("./Tests/Resources/sephiroth.png"))
			throw std::runtime_error("Cannot read image from file");
		img1->setVisible(true);
		img2->setVisible(true);

		GF::Core::MemGuard<Texture2D> tmpT=img1->exportTexture();
		multi.append(tmpT);

		Sounds::Music music;
		music.openFromFile("./Tests/Resources/music.ogg");
		music.setLoop(true);
		music.play();
		window.Show();
		music.stop();

		std::cout << "\nDo you can control characters(on keys) and moving background when characters moving? (Y/N)\n";
		std::cin >> resp;
		if (resp != 'y' && resp != 'Y') result += "Characters or camera error\n";
		std::cout << "\nDo you hear a music? (Y/N)\n";
		std::cin >> resp;
		if (resp != 'y' && resp != 'Y') result += "Music plaing error\n";
	}
	catch (std::exception e) {
		return std::string("Catched exception: ") + e.what();
	}
	catch (std::exception *e) {
		return std::string("Catched exception: ") + e->what();
	}
		
	return result;
}