#include "../GameEngine/RTGameEngine.h"
#include "../GameEngine/TurnGameEngine.h"
#include "../GameEngine/Map2D.h"
#include "../GameEngine/Model2D.h"
#include "../GameEngine/Mob.h"
#include "../GameEngine/StaticObject.h"

#include "Tests.h"
std::string Test14();
AutoAdd AA14(Test14, "GameEngine", "Search objects Test");

namespace Test14Helpers {
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

	class StaticObjectTest :public GF::GameEngine::StaticObject {
	public:
		StaticObjectTest() {
			model = new GF::GameEngine::Model2D({ 1,1 });
		}
		StaticObjectTest(GF::GameEngine::Model2D &m) {
			model = m;
		}
	};
}


std::string Test14() {
	std::string result;
	using namespace GF::GameEngine;
	using namespace Test14Helpers;
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
		StaticObjectTest s1(m1), s2(m2), s3(m3), s4(m4);

		s1.setPos({ 18,10 }); s2.setPos({ 90,20 }); s3.setPos({ 50,20 }); s4.setPos({ 0,0 });
		ge.addStaticObject(s1); ge.addStaticObject(s2); ge.addStaticObject(s3); ge.addStaticObject(s4);

		std::vector<GF::Core::MemGuard<GameObject>> objs;
		std::list<unsigned long long> objs1;
		std::list<unsigned long long> objs2;
		std::list<GF::Core::MemGuard<GameObject>> objs3;

		objs = ge.scanRect({ 21,10,51,21 });
		if (objs.size() != 2) result += "Error in rect scanning v1\n";
		objs = ge.scanRect({ 0,0,100,30 });
		if (objs.size() != 4) result += "Error in rect scanning v2\n";
		objs = ge.scanRect({ 50,10,10,20 });
		if (objs.size() != 1) result += "Error in rect scanning v3\n";
		objs = ge.scanRect({ 61,10,10,20 });
		if (objs.size() != 0) result += "Error in rect scanning v4\n";

		if (ge.whatIsOn({ 20,11 }) != &s1)result += "Error in pos scanning v1\n";
		if (ge.whatIsOn({ 0,0 }) != &s4)result += "Error in pos scanning v2\n";
		if (ge.whatIsOn({ 50,10 }) != nullptr)result += "Error in pos scanning v3\n";

		s4.setPos({ 81, 21 });
		if (s4.getPos().x != 81 || s4.getPos().y != 21) result += "Moving object error\n";

		objs = ge.detectOnLine({ 0,10 }, { 1,0 });
		if (objs.size() != 1)result += "Error in line scanning v1.1\n";
		objs = ge.detectOnLine({ 0,20 }, { 1,0 });
		if (objs.size() != 2)result += "Error in line scanning v1.2\n";
		objs = ge.detectOnLine({ 100,10 }, { -1,0 });
		if (objs.size() != 1)result += "Error in line scanning v2.1\n";
		objs = ge.detectOnLine({ 100,20 }, { -1,0 });
		if (objs.size() != 2)result += "Error in line scanning v2.2\n";
		objs = ge.detectOnLine({ 70,0 }, { 1,1 });
		if (objs.size() != 1)result += "Error in line scanning v3.1\n";
		objs = ge.detectOnLine({ 60,0 }, { 1,1 });
		if (objs.size() != 1)result += "Error in line scanning v3.2\n";
		objs = ge.detectOnLine({ 100,30 }, { -1,-1 });
		if (objs.size() != 1)result += "Error in line scanning v4.1\n";
		objs = ge.detectOnLine({ 90,30 }, { -1,-1 });
		if (objs.size() != 1)result += "Error in line scanning v4.2\n";

		objs = ge.detectOnLine({ 81,0 }, { 0,1 });
		if (objs.size() != 1)result += "Error in line scanning v5.1\n";
		objs = ge.detectOnLine({ 50,30 }, {0,-1 });
		if (objs.size() != 1)result += "Error in line scanning v5.2\n";


		for (int i = 0; i < 30; i++) {
			delete[] mapPtr[i];
		}
		delete[] mapPtr;
	}
	catch (std::exception e) {
		result += "Catched exception: " + std::string(e.what());
	}
	catch (...){}
	return result;
}