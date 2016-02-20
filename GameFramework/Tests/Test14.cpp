#include "../GameEngine/RTGameEngine.h"
#include "../GameEngine/TurnGameEngine.h"
#include "../GameEngine/Map2D.h"

#include "Tests.h"
std::string Test14();
AutoAdd AA14(Test14, "GameEngine", "Sectors calculating Test", true);

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


		for (int i = 0; i < 30; i++) {
			delete[] mapPtr[i];
		}
		delete[] mapPtr;
	}
	catch (std::exception e) {
		result += "Catched exception: " + std::string(e.what());
	}
	return result;
}