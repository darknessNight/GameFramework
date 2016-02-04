#pragma once
#include "../stdafx.h"
#include "../IOModule/Window.h"

namespace Test2Helpers {
	std::string results;
	bool testDelTest2 = false;

	void JoystickButtonDelTest(void* sender, GameFramework::IOModule::Events::JoystickButtArgs &args) {
		results += "Don't delete event\n";
	}

	void JoystickButtonDelTest2(void* sender, GameFramework::IOModule::Events::JoystickButtArgs &args) {
		testDelTest2 = true;
	}

	void JoystickMoveTest(void* sender, GameFramework::IOModule::Events::JoystickMoveArgs &args) {
		if (args.axis != GameFramework::IOModule::Joystick::Axis::U || args.joystickId != 1)
			results += "Error of args\n";
	}

	class Test {
	public:
		static int i;
		void JoystickButtonDelTest(void* sender, GameFramework::IOModule::Events::JoystickButtArgs &args) {
			if (i > 0)results += "Don't delete event v2\n";
			i++;
		}
		static void DelTestResult() {
			if (i == 0)results += "Delete all events of class\n";
			if(!testDelTest2)results += "Delete all events\n";
			i = 0;
			testDelTest2 = false;
		}
	};
	int Test::i = 0;
}


std::string Test2() {
	try {
		//tests for starting and closing window
		GameFramework::IOModule::Window window;
		window.ShowAsync();
		using namespace std::literals;
		std::this_thread::sleep_for(2s);
		window.Close();
		window.Close();

		//tests for events' support
		sf::Event ev;
		ev.key.alt = true;
		ev.key.code = GameFramework::IOModule::Keyboard::Dash;

		Test2Helpers::Test ob1, ob2;

		//tests for adding and deleting events' functions
		int id = window.JoystickButtonPress += Test2Helpers::JoystickButtonDelTest;
		window.JoystickButtonPress -= id;
		window.JoystickButtonPress += Test2Helpers::JoystickButtonDelTest2;
		id = window.JoystickButtonPress += std::bind(&Test2Helpers::Test::JoystickButtonDelTest, ob1, std::placeholders::_1, std::placeholders::_2);
		window.JoystickButtonPress += std::bind(&Test2Helpers::Test::JoystickButtonDelTest, ob2, std::placeholders::_1, std::placeholders::_2);
		window.JoystickButtonPress -= id;
		window.JoystickMove += Test2Helpers::JoystickMoveTest;
		window.ShowAsync();
		std::this_thread::sleep_for(1s);

		ev.joystickButton.joystickId = 1;
		ev.joystickMove.axis = GameFramework::IOModule::Joystick::Axis::U;
		window.TestEvents(ev);

		Test2Helpers::Test::DelTestResult();

		window.JoystickButtonPress.clear();

		window.JoystickButtonPressAsync += Test2Helpers::JoystickButtonDelTest2;
		id = window.JoystickButtonPressAsync += std::bind(&Test2Helpers::Test::JoystickButtonDelTest, ob1, std::placeholders::_1, std::placeholders::_2);
		window.JoystickButtonPressAsync += std::bind(&Test2Helpers::Test::JoystickButtonDelTest, ob2, std::placeholders::_1, std::placeholders::_2);
		window.JoystickButtonPressAsync -= id;

		std::this_thread::sleep_for(1s);
		window.TestEvents(ev);

		Test2Helpers::Test::DelTestResult();

		window.Close();
	}
	catch (std::exception e) {
		return e.what();
	}
	catch (std::exception *e) {
		return e->what();
	}
	return Test2Helpers::results;
}