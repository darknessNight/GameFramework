/*
Test obs³ugi w¹tków.
*/

#pragma once
#include "../../GameFramework/IOModule/Window.h"
#include "../../GameFramework/IOModule/Sound.h"
#include "../../GameFramework/Core/Timer.h"

#include "Tests.h"
std::string Test10();
AutoAdd AA10(Test10, "Core", "shared_ptr Test");

namespace Test10Helpers {
	using namespace GF::Core;
	std::string result;
	shared_ptr<int> str;
	void ChangeStrEnd() {
		str.lockPtr();
		for (int i = 1; i <= 3; i++) {
			(*str)++;
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
		str.unlockPtr();
	}

	void ChangeStrStart() {
		if ((*str) != 3) result += "Mutex blocking in shared_ptr doesn't work correctly";
	}
}

std::string Test10() {
	using namespace Test10Helpers;
	using namespace GF;
	using namespace GF::IOModule;
	using namespace GF::Core;
	using namespace std::literals;
	char ret;

	char cstr[] = "Ala ma kota, kot ma alê";

	int i = 0;
	str = i;
	try {
		std::thread th1(ChangeStrEnd);
		std::this_thread::sleep_for(std::chrono::microseconds(100));
		std::thread th2(ChangeStrStart);
		th1.join();
		th2.join();
	}
	catch (std::exception e) {
		result += "Catched error: " + std::string(e.what());
	}

	return result;
}