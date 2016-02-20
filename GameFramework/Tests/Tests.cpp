#include "Tests.h"
#include <vector>
#include <iostream>
#include <string>
#ifdef DEBUG
#include "../MemGuard.h"
#endif


static std::vector<std::string(*)()>* funcs;
static std::vector<std::string>* cName;
static std::vector<std::string>* sName;
static unsigned* lastF;

void AddToList(std::string(*f)(), std::string suitName, std::string caseName)
{
	if (funcs == nullptr) funcs = new std::vector<std::string(*)()>;
	funcs->push_back(f);
	if (cName == nullptr) cName = new std::vector<std::string>;
	cName->push_back(caseName);
	if (sName == nullptr) sName = new std::vector<std::string>;
	sName->push_back(suitName);
}

std::string Tests(int start, int stop) {
	//funcs.push_back(Test10);
	std::vector<std::string(*)()> &funcs = *::funcs;

	std::string ret;
	std::string results;
#ifdef  TEST_ALL
	for (int i = __min(__max(start - 1, 0),funcs.size()-1); i < __min(stop, funcs.size()); i++) {
		system("cls");
		std::cout << "Test " << (*cName)[i]<<":"<<(*sName)[i] << "\n----------------------------------------------\n";
		ret = funcs[i]();
		results += "\n Test " + (*cName)[i] + ":" + (*sName)[i] + " result: ";
		if (ret.size() > 0)results += '\n' + ret;
		else results += "OK";
	}
#else
	if (lastF != nullptr) {
		system("cls");
		std::cout << "Test " << (*cName)[*lastF] << ":" << (*sName)[*lastF] << "\n----------------------------------------------\n";
		ret = funcs[*lastF]();
		results += "\n Test " + (*cName)[*lastF] + ":" + (*sName)[*lastF] + " result: ";
		if (ret.size() > 0)results += '\n' + ret;
		else results += "OK";
	}
#endif //  TEST_ALL
	return results;
}

AutoAdd::AutoAdd(std::string(*f)(), std::string suitName, std::string caseName, bool last)
{
	AddToList(f, suitName, caseName);
	if (last) {
		lastF = new unsigned;
		(*lastF) = funcs->size() - 1;
	}
}
