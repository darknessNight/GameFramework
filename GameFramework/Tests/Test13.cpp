#include "../GameEngine/RTGameEngine.h"
#include "../GameEngine/TurnGameEngine.h"
#include "../GameEngine/Map2D.h"

#include "Tests.h"
std::string Test13();
AutoAdd AA13(Test13, "GameEngine", "Sectors calculating Test");

namespace Test13Helpers {
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


std::string Test13() {
	std::string result;
	using namespace GF::GameEngine;
	using namespace Test13Helpers;
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

		if (ge.xSectors*ge.sectSize.width <100 || ge.ySectors*ge.sectSize.height <30 || ge.zSectors!=0) result += "Error in sectors calc\n";
		if (ge.calcSector({ map.getSize().width-1,map.getSize().height-1,map.getSize().depth }) != ge.xSectors*ge.ySectors-1) result += "Error in sector from pos calc\n";
		if (ge.calcSector({ 1,1,0 }) != 0) result += "Error in sector from zero pos calc\n";
		ge.setCountOfSectors(20);
		if (ge.xSectors*ge.sectSize.width <100 || ge.ySectors*ge.sectSize.height <30 || ge.zSectors != 0) result += "Error in sectors calc v2\n";
		if (ge.calcSector({ map.getSize().width-1,map.getSize().height-1,map.getSize().depth }) != ge.xSectors*ge.ySectors - 1) result += "Error in sector from pos calc v2\n";

		ge.setCountOfSectors(30);
		if (ge.xSectors*ge.sectSize.width <100 || ge.ySectors*ge.sectSize.height <30 || ge.zSectors != 0) result += "Error in sectors calc v3\n";
		if (ge.calcSector({ map.getSize().width-1,map.getSize().height-1,map.getSize().depth }) != ge.xSectors*ge.ySectors - 1) result += "Error in sector from pos calc v3\n";
		if (ge.calcSector({ map.getSize().width - 1,1,map.getSize().depth }) != ge.xSectors - 1) result += "Error in sector from pos calc v4\n";
		if (ge.calcSector({ 1,map.getSize().height - 1,map.getSize().depth }) != (ge.xSectors)*(ge.ySectors-1)) result += "Error in sector from pos calc v5\n";

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