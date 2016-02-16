/*
Test obs³ugi Timera.
*/

#pragma once
#include "../../GameFramework/Core/Timer.h"
#include "../../GameFramework/IOModule/Window.h"

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
		i1 = 0;
		Timer t1, t2;
		t1.Tick += incr1;
		t1.setInterval(std::chrono::milliseconds(100));
		t1.startAsync();
		std::this_thread::sleep_for(std::chrono::milliseconds(2150));
		t1.stop();
		if (i1<20)result += "Timer1 not working i1:" + std::to_string(i1) + "\n";
		i1 = 0;
		t2.Tick += decr1;
		t2.setInterval(std::chrono::milliseconds(200));

		t1.startAsync();
		t2.startAsync();
		std::this_thread::sleep_for(std::chrono::milliseconds(2050));
		t1.stop();
		t2.stop();

		if (i1<8 || i1>12)result += "Timer2 not working i1:" + std::to_string(i1) + "\n";

	}
	catch (std::exception e) {
		result += "Catched error: " + std::string(e.what());
	}

	return result;
}