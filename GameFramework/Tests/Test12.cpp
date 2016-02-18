/*
Test obs³ugi menu
*/

#pragma once
#include "../GameEngine/Map2D.h"
#include "../GameEngine/Model2D.h"

namespace Test12Helpers {
	
}


std::string Test12() {
	using namespace Test12Helpers;
	using namespace GF::GameEngine;
	std::string result;
	char ret;

	try {
		bool **map1;
		map1 = new bool*[3];
		for (int i = 0; i < 3; i++) {
			map1[i] = new bool[3];
			memset(map1[i], false, 3 * sizeof(bool));
		}
		map1[0][0] = map1[0][1] = 
		map1[1][0] = map1[1][2] = 
		map1[2][1] = map1[2][2] = true;
		//xxo
		//xox
		//oxx

		Map2D m1(map1, 3, 3);
		Model2D mod1({ 1,1 }), mod2({ 1,1 },Model2D::CollideType::NonCollide);
		if (m1.isMovePosible({1,1}, { 0,1 }, &mod1) == true) result += "Don't detect y+1;Collide\n";
		if (m1.isMovePosible({ 0,1 }, { 0,1 }, &mod1) == false) result += "Don't detect y+1;NonCollide\n";

		if (m1.isMovePosible({ 1,1 }, { 0,-1 }, &mod1) == true) result += "Don't detect y-1;Collide\n";
		if (m1.isMovePosible({ 2,1 }, { 0,-1 }, &mod1) == false) result += "Don't detect y-1;NonCollide\n";

		if (m1.isMovePosible({ 1,1 }, { 1,0 }, &mod1) == true) result += "Don't detect x+1;Collide\n";
		if (m1.isMovePosible({ 1,0 }, { 1,0 }, &mod1) == false) result += "Don't detect x+1;NonCollide\n";

		if (m1.isMovePosible({ 1,1 }, { -1,0 }, &mod1) == true) result += "Don't detect x-1;Collide\n";
		if (m1.isMovePosible({ 1,2 }, { -1,0 }, &mod1) == false) result += "Don't detect x-1;NonCollide\n";

		if (m1.isMovePosible({ 1,1 }, { 1,1 }, &mod1) == true) result += "Don't detect xy+1;Collide\n";
		if (m1.isMovePosible({ 0,0 }, { 1,1 }, &mod1) == false) result += "Don't detect xy+1;NonCollide\n";

		if (m1.isMovePosible({ 2,1 }, { -1,1 }, &mod1) == true) result += "Don't detect x-1y+1;Collide\n";
		if (m1.isMovePosible({ 1,1 }, { -1,1 }, &mod1) == false) result += "Don't detect x-1y+1;NonCollide\n";

		if (m1.isMovePosible({ 0,1 }, { 1,-1 }, &mod1) == true) result += "Don't detect x+1y-1;Collide\n";
		if (m1.isMovePosible({ 1,1 }, { 1,-1 }, &mod1) == false) result += "Don't detect x+1y-1;NonCollide\n";

		if (m1.isMovePosible({ 1,1 }, { -1,-1 }, &mod1) == true) result += "Don't detect xy-1;Collide\n";
		if (m1.isMovePosible({ 2,2 }, { -1,-1 }, &mod1) == false) result += "Don't detect xy-1;NonCollide\n";

		if (m1.isMovePosible({ 2,1 }, { 0,-2 }, &mod1) == true) result += "Don't detect y-2;Collide\n";
		if (m1.isMovePosible({ 1,0 }, { 2,0 }, &mod1) == true) result += "Don't detect x+2;Collide\n";

		map1[0][1] = map1[1][2] = false;
		if (m1.isMovePosible({ 1,2 }, { 0,-2 }, &mod1) == true) result += "Don't detect y-2;NonCollide\n";
		if (m1.isMovePosible({ 0,1 }, { 2,0 }, &mod1) == true) result += "Don't detect x+2;NonCollide\n";

		if (m1.isMovePosible({ 1,1 }, { 0,1 }, &mod2) == false) result += "NonCollide option doesn't work\n";

		for (int i = 0; i < 3; i++) {
			delete[] map1[i];
		}
		delete[] map1;

		map1 = new bool*[30];
		for (int i = 0; i < 30; i++) {
			map1[i] = new bool[90];
			memset(map1[i], false, 90 * sizeof(bool));
		}

		Model2D mod3({ 3,3 }), mod4({ 10,10 });
		bool *modelMap[10];
		for (int i = 0; i < 10; i++) {
			modelMap[i] = new bool[10];
			memset(modelMap[i], false, 10 * sizeof(bool));
			modelMap[i][i] = modelMap[i][9 - i] = true;
		}
		mod4.setMap(modelMap, 10, 10);

		for (int i = 0; i < 10; i++) {
			delete[] modelMap[i];
		}

		for (int i = 0; i < 30; i++)
			map1[i][45]=true;

		m1.setMap(map1, 90, 30);
		if(m1.isMovePosible({ 0,0 }, { 80,20 }, &mod3)!=false) result += "Move on big map. Simple wall. Don't detect collide: small object\n";
		if (m1.isMovePosible({ 0,0 }, { 80,20 }, &mod4) != false) result += "Move on big map. Simple wall. Don't detect collide: big object\n";
		
		for (int i = 0; i < 30; i++)
			map1[i][45] = false;

		for (int i = 0; i < 30; i++)
			map1[i][60-i] = true;

		m1.setMap(map1, 90, 30);
		if (m1.isMovePosible({ 0,0 }, { 80,20 }, &mod3) != false) result += "Move on big map. Slash wall. Horizontal move. Don't detect collide: small object\n";
		if (m1.isMovePosible({ 0,0 }, { 80,20 }, &mod4) != false) result += "Move on big map. Slash wall. Horizontal move. Don't detect collide: big object\n";

		if (m1.isMovePosible({ 30,0 }, { 20,20 }, &mod3) != false) result += "Move on big map. Slash wall. Slash move. Don't detect collide: small object\n";
		if (m1.isMovePosible({ 30,0 }, { 20,20 }, &mod4) != false) result += "Move on big map. Slash wall. Slash move. Don't detect collide: big object\n";

		if (m1.isMovePosible({ 30,0 }, { 20,0 }, &mod3) != true) result += "Move on big map. Slash wall. Slash move. Don't touch wall. Don't detect collide: small object\n";
		if (m1.isMovePosible({ 30,0 }, { 10,0 }, &mod4) != true) result += "Move on big map. Slash wall. Slash move. Don't touch wall. Don't detect collide: big object\n";

		if (m1.isMovePosible({ 40,0 }, { 25,25 }, &mod1) != false) result += "Move on big map. Slash wall. Slash move. Don't detect collide: dot object\n";
		if (m1.isMovePosible({ 28,0 }, { 15,15 }, &mod1) != true) result += "Move on big map. Slash wall. Slash move. Move possible Don't detect collide: dot object\n";

		Pos p1 = m1.moveResult({ 30,0 }, { 20,20 }, &mod4);
		std::clog << p1.x << ":" << p1.y << "\n";
		p1 = m1.moveResult({ 40,0 }, { 25,25 }, &mod1);
		std::clog << p1.x << ":" << p1.y << "\n";

		system("pause");

		for (int i = 0; i < 10; i++) {
			delete[] map1[i];
		}
		delete[] map1;

	}
	catch (std::exception e) {
		result += "Catched error: " + std::string(e.what());
	}

	return result;
}