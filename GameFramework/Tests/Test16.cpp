#include "../GameEngine/RTGameEngine.h"
#include "../GameEngine/TurnGameEngine.h"
#include "../GameEngine/Map2D.h"
#include "../GameEngine/Model2D.h"
#include "../GameEngine/Mob.h"
#include "../GameEngine/StaticObject.h"
#include "../Core/Exception.h"
#include "../../GameFramework/IOModule/Window.h"
#include "../../GameFramework/IOModule/Image.h"
#include "../../GameFramework/IOModule/MultipleGraph.h"
#include "../../GameFramework/IOModule/Sound.h"
#include <fstream>

#include "Tests.h"
std::string Test16();
AutoAdd AA16(Test16, "GameEngine/IOModule", "Synch test", true);


namespace Test16Helpers {
	using namespace std::chrono;
	using namespace GF::IOModule;
	Camera cam1, cam2;
	GF::Core::shared_ptr<Image> img1, img2, img3, img4;
	long long ind = 0;
	std::chrono::time_point<std::chrono::steady_clock> started = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> render;
	int frameCount = 0;
	GF::Core::shared_ptr<GF::IOModule::Texture2D> texture1;
	GF::Core::shared_ptr<GF::IOModule::Texture2D> texture2;
	typedef std::chrono::duration<double, std::micro> timeDur;
	typedef std::chrono::duration<double, std::milli> timeDur2;
	typedef std::chrono::duration<double, std::ratio<1, 1000> > timeDurMove;

	void ControlImage(GF::IOModule::Events::EventArgs& args) {

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
		if (args.code == Keyboard::P)
			((Window*)args.sender)->captureToFile("./Tests/Test4Window.png");
	}

	void Collide(GF::GameEngine::CollisionEventArgs &args) {
		GF::IOModule::Shapes::Rectangle rect;
		rect.setSize({ 128,192 });
		rect.setFillColor(Color::Blue);
		rect.setOutlineColor(Color::White);
		rect.setOutlineThickness(2.1f);
		img3->draw(rect);
		img4->draw(rect);
	}


	class GameEngineTest :public GF::GameEngine::GameEngine {
	public:
		bool play = false;
		using GameEngine::xSectors;
		using GameEngine::ySectors;
		using GameEngine::zSectors;
		using GameEngine::sectSize;
		using GameEngine::calcSector;
		virtual void start() {
			play = true; 
			while (play) {
				for each(auto mob in this->mobs) {
					mob->doScript();
				}
				std::this_thread::sleep_for(1ms);
			}
		};
		virtual void stop() {
			play = false;
		};
		virtual void pause() {};
		using GameEngine::sectors;
		using GameEngine::physCountOfSectors;
		using GameEngine::staticObjects;
	} ge;

	void Close(GF::IOModule::Events::KeyboardArgs &args) {
		if (args.code == GF::IOModule::Keyboard::Escape) {
			((GF::IOModule::Window*)args.sender)->Close();
			ge.stop();
		}
	}

	class MobTest :public GF::GameEngine::Mob {
	public:
		MobTest(GF::GameEngine::Model2D &m, Camera &c, GF::Core::shared_ptr<Image> &i) {
			model = m;
			cam = &c;
			img = i;
		}
	public:
		GF::Core::shared_ptr<Image> img;
		steady_clock::time_point now, last = high_resolution_clock::now();
		Camera *cam=nullptr;
		GF::IOModule::Posf pos = { 0,0 };
		//bool doScript()override { return false; };
	};
	class MobTest1 :public MobTest {
		using MobTest::MobTest;
		bool doScript()override {
			now = high_resolution_clock::now();
			float TIP = duration_cast<milliseconds>(now - last).count() / 2.0f;
			last = now;
			float mx=0, my=0;
			if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::W)) { my = -TIP; }
			if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::S)) { my = TIP; }
			if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::A)) { mx = -TIP; }
			if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::D)) { mx = TIP; }
			GF::GameEngine::Pos tmp = move({ mx, my,0 });
			if (tmp.x > 0 && tmp.y > 0) {
				pos = { tmp.x,tmp.y };
				if (mx != 0 || my != 0)
				std::cout << pos.x << " " << pos.y << "\n";
				cam->setCenter(pos);
				img->setPosition(pos);
				img3->setPosition(pos);
			}
			return true;
		}
	};

	class MobTest2 :public MobTest {
		using MobTest::MobTest;
		bool doScript()override {
			now = high_resolution_clock::now();
			float TIP = duration_cast<milliseconds>(now - last).count() / 2.0f;
			last = now;

			float mx = 0, my = 0;
			if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::Up)) { my = -TIP; }
			if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::Down)) { my = TIP; }
			if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::Left)) { mx = -TIP; }
			if (GF::IOModule::Keyboard::isKeyPressed(GF::IOModule::Keyboard::Right)) { mx = TIP; }
			GF::GameEngine::Pos tmp = move({ mx, my,0 });
			if (tmp.x > 0 && tmp.y > 0) {
				pos = { tmp.x,tmp.y };
				if (mx != 0 || my != 0)
				std::cout << pos.x << " " << pos.y << ":\n";
				cam->setCenter(pos);
				img->setPosition(pos);
				img4->setPosition(pos);
			}

			return true;
		}
	};
}

std::string Test16() {

	std::string result;
	using namespace GF::GameEngine;
	using namespace Test16Helpers;
	using namespace GF::IOModule;
	try {
		using namespace Test16Helpers;
		char resp = 0;
		GF::IOModule::Window window;
		window.setTitle("Test16");
		window.KeyPressed += SaveWindow;
		window.KeyPressed += Test16Helpers::Close;
		//window.Render += ControlImage;
		window.setVerticalSyncEnabled(true);
		start = std::chrono::high_resolution_clock::now();

		texture1 = window.CreateTexture({ 1280,1024 });
		GF::Core::shared_ptr<Texture2D> tmp = window.CreateTexture({ 1280,1024 });
		texture1->setVisible(true);
		texture1->setOrigin({ 50,50 });
		if (!texture1->loadFromFile("./Tests/Resources/img2.jpg"))
			throw std::runtime_error("Cannot read image from file");
		texture1->setPosition({ 0,0 });
		texture1->setVisible(true);

		cam1.setSize({ 600,900 });
		cam1.setViewport({ 0,0,0.49f,1 });
		cam2.setSize({ 600,900 });
		cam2.setViewport({ 0.51f,0,0.5f,1 });

		window.appendCamera(cam2);
		window.appendCamera(cam1);


		GF::IOModule::Shapes::Rectangle rect;
		rect.setSize({ 128,192 });
		img3 = window.CreateImage({ 128,192 }, 99);;
		img4 = window.CreateImage({ 128,192 }, 99);
		rect.setFillColor(Color::Red);
		img3->draw(rect);
		rect.setFillColor(Color::Yellow);
		img4->draw(rect);
		img3->setVisible(true);
		img4->setVisible(true);

		img1 = window.CreateImage({ 192,256 }, 99);
		img2 = window.CreateImage({ 128,192 }, 99);

		MultipleGraph2D multi({ 192,256 });
		Camera pm1({ 0,8 + 2 * 64, 48,60 }), pm2({ 0,0, 36,48 });
		img1->setScale({ 0.75f,0.75f });
		img1->appendCamera(pm1);
		img2->appendCamera(pm2);
		img1->setSmooth(true);
		img2->setSmooth(true);
		if (!img1->loadFromFile("./Tests/Resources/alex.png"))
			throw std::runtime_error("Cannot read image from file");
		if (!img2->loadFromFile("./Tests/Resources/sephiroth.png"))
			throw std::runtime_error("Cannot read image from file");
		img1->setVisible(true);
		img2->setVisible(true);

		GF::Core::shared_ptr<Texture2D> tmpT = img1->exportTexture();
		multi.append(tmpT);


		Map2D map(1280, 1024);
		ge.appendMap(map);


		Model2D m1({ 128,192 }), m2({ 128,192 }), m3({ 10,3 }), m4({ 9,4 });
		MobTest1 s1(m1,cam1,img1);
		MobTest2 s2(m2,cam2,img2);

		s1.setPos({ 18,10 }); s2.setPos({ 300,300 });
		s1.Collision += Collide; s2.Collision += Collide;
		ge.addMob(s1); ge.addMob(s2);

		window.ShowAsync();
		ge.start();
		
		std::cout << "\nDo you can control characters(on keys) and moving background when characters moving? (Y/N)\n";
		std::cin >> resp;
		if (resp != 'y' && resp != 'Y') result += "Characters or camera error\n";
	}
	catch (std::exception e) {
		return std::string("Catched exception: ") + e.what();
	}
	catch (std::exception *e) {
		return std::string("Catched exception: ") + e->what();
	}

	return result;
}