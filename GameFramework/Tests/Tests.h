#pragma once
#include "../../GameFramework/IOModule/Window.h"
#include "../../GameFramework/IOModule/Sound.h"

void AddToList(std::string(*f)(),std::string caseName, std::string suitName);

class AutoAdd {
public:
	AutoAdd(std::string(*f)(), std::string caseName, std::string suitName);
};

std::string Tests(int start, int stop);
void Close(GF::IOModule::Events::KeyboardArgs &args);