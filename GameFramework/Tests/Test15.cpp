#include "../GameEngine/RTGameEngine.h"
#include "../GameEngine/TurnGameEngine.h"
#include "../GameEngine/Map2D.h"
#include "../GameEngine/Model2D.h"
#include "../GameEngine/Mob.h"
#include "../GameEngine/StaticObject.h"
#include "../Core/Exception.h"

#include "Tests.h"
std::string Test15();
AutoAdd AA15(Test15, "GameEngine", "Search objects Test", false);

namespace Test15Helpers {
	class GameEngineTest :public GF::GameEngine::GameEngine {
	public:
		using GameEngine::xSectors;
		using GameEngine::ySectors;
		using GameEngine::zSectors;
		using GameEngine::sectSize;
		using GameEngine::calcSector;
		virtual void start() {};
		virtual void stop() {};
		virtual void pause() {};
		using GameEngine::sectors;
		using GameEngine::physCountOfSectors;
		using GameEngine::staticObjects;
	};

	class MobTest :public GF::GameEngine::Mob {
	public:
		MobTest() {
			model = new GF::GameEngine::Model2D({ 1,1 });
		}
		MobTest(GF::GameEngine::Model2D &m) {
			model = m;
		}
		bool doScript()override { return false; };
	};
}


std::string Test15() {
	std::string result;
	using namespace GF::GameEngine;
	using namespace Test15Helpers;
	try {
		GameEngineTest ge;
		Map2D map;
		bool **mapPtr;
		mapPtr = new bool*[30];
		for (int i = 0; i < 30; i++) {
			mapPtr[i] = new bool[100];
			memset(mapPtr[i], false, 100 * sizeof(bool));
		}
		map.setMap(mapPtr, 100, 30);
		ge.appendMap(map);

		Model2D m1({ 10,9 }), m2({ 5,5 }), m3({ 10,3 }), m4({ 9,4 });
		MobTest s1(m1), s2(m2), s3(m3), s4(m4);

		s1.setPos({ 18,10 }); s2.setPos({ 90,20 }); s3.setPos({ 50,20 }); s4.setPos({ 60,0 });
		ge.addMob(s1); ge.addMob(s2); ge.addMob(s3); ge.addMob(s4);

		Pos test;

		s1.move({ 10,10 });
		if (s1.getPos() != Pos({ 28,20 })) result += "Simple move non collision failed v1\n";
		s1.move({ 0,-10 });
		if (s1.getPos() != Pos({ 28,10 })) result += "Simple move non collision failed v2\n";
		s1.move({ -10,0 });
		if (s1.getPos() != Pos({ 18,10 })) result += "Simple move non collision failed v3\n";
		s1.move({ -10,-10 });
		if (s1.getPos() != Pos({ 8,0 })) result += "Simple move non collision failed v4\n";
		s1.move({ 10,10 });
		if (s1.getPos() != Pos({ 18,10 })) result += "Simple move non collision failed v5\n";

		s2.move({ -40,0 });
		if (s2.getPos() != Pos({ 60,20 })) result += "Simple move. Collision. failed v1\n";
		s2.setPos({ 90,20 });

		s3.move({ 40,0 });
		if (s3.getPos() != Pos({ 80,20 })) result += "Simple move. Collision. failed v2\n";

		s4.move({ 20,20 });
		test = s4.getPos();
		if (s4.getPos() != Pos({ 76,16 })) result += "Simple move. Collision. failed v3\n";

		s4.setPos({ 60,0 });
		s3.move({ -20,-20 });
		if (s3.getPos() != Pos({ 69,9 })) result += "Simple move. Collision. failed v4\n";

		for (int i = 0; i < 30; i++) {
			delete[] mapPtr[i];
		}
		delete[] mapPtr;
	}
	catch (std::exception e) {
		result += "Catched exception: " + std::string(e.what());
	}
	catch (...) {}
	return result;
}