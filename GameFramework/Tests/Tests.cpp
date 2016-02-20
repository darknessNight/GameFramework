#include "Tests.h"
#include <string>

static std::vector<std::string(*)()>* funcs;
static std::vector<std::string>* cName;
static std::vector<std::string>* sName;

void AddToList(std::string(*f)(), std::string caseName, std::string suitName)
{
	if (funcs == nullptr) funcs = new std::vector<std::string(*)()>;
	funcs->push_back(f);
	if (cName == nullptr) cName = new std::vector<std::string>;
	cName->push_back(caseName);
	if (sName == nullptr) sName = new std::vector<std::string>;
	sName->push_back(suitName);
}

std::string Tests(int start, int stop) {
	std::vector<std::string(*)()> &funcs = *::funcs;

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

AutoAdd::AutoAdd(std::string(*f)(), std::string caseName, std::string suitName)
{
	AddToList(f, caseName, suitName);
}
