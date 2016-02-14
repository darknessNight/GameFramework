#include "Tests.h"

std::vector<std::string(*)()> funcs;

std::string Tests(int start, int stop) {
	funcs.push_back(Test1);
	funcs.push_back(Test2);
	funcs.push_back(Test3); 
	funcs.push_back(Test4); 
	funcs.push_back(Test5);
	funcs.push_back(Test6);
	funcs.push_back(Test7);
	funcs.push_back(Test8);
	funcs.push_back(Test9);
	funcs.push_back(Test10);
	funcs.push_back(Test11);
	//funcs.push_back(Test10);

	std::string ret;
	std::string results;
	for (int i = __min(__max(start - 1, 0),funcs.size()-1); i < __min(stop, funcs.size()); i++) {
		system("cls");
		std::clog << "Test" << i + 1 << "\n----------------------------------------------\n";
		ret = funcs[i]();
		results += "\n Test " + std::to_string(i + 1) + " result: ";
		if (ret.size() > 0)results += '\n' + ret;
		else results += "OK";
	}
	return results;
}

void Close(GF::IOModule::Events::KeyboardArgs &args) {
	if (args.code == GF::IOModule::Keyboard::Escape)
		((GF::IOModule::Window*)args.sender)->Close();
}