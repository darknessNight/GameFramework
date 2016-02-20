#pragma once
#include <string>
void AddToList(std::string(*f)(),std::string suitName, std::string caseName);

class AutoAdd {
public:
	AutoAdd(std::string(*f)(), std::string suitName, std::string caseName, bool last = false);
};

std::string Tests(int start, int stop);