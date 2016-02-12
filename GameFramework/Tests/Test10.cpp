/*
Test obs³ugi w¹tków.
*/

#pragma once
#include "../IOModule/Window.h"
#include "../IOModule/Sound.h"
#include "../Core/Timer.h"

namespace Test9Helpers {
}

std::string Test9() {
	std::string result;
	int i1;
	using namespace Test9Helpers;
	using namespace GF;
	using namespace GF::IOModule;
	using namespace GF::Core;
	using namespace std::literals;
	char ret;

	auto incr1 = std::function<void(GF::Core::Events::EventArgs&)>([&](GF::Core::Events::EventArgs&) {i1++; });
	auto decr1 = std::function<void(GF::Core::Events::EventArgs&)>([&](GF::Core::Events::EventArgs&) {i1--; });

	try {
	}
	catch (std::exception e) {
		result += "Catched error: " + std::string(e.what());
	}

	return result;
}