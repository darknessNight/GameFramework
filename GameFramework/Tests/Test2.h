#pragma once
#include "../stdafx.h"
#include "../IOModule/Window.h"
using namespace GF::IOModule::Events;
using namespace std::literals;
namespace Test2Helpers {
	std::string results;
	bool testDelTest2 = false;

	void JoystickButtonDelTest(GF::IOModule::Events::JoystickButtArgs &args) {
		results += "Don't delete event\n";
	}

	void JoystickButtonDelTest2(GF::IOModule::Events::JoystickButtArgs &args) {
		testDelTest2 = true;
	}

	void JoystickMoveTest(GF::IOModule::Events::JoystickMoveArgs &args) {
		if (args.axis != GF::IOModule::Joystick::Axis::U || args.joystickId != 1 || args.position != 132)
			results += "Error of args\n";
	}

	class Test :public GF::Core::Object {
	public:
		typedef void(Object::*rzut)(JoystickButtArgs&);
		static int i;
		void JoystickButtonDelTest(GF::IOModule::Events::JoystickButtArgs &args) {
			if (i > 0)results += "Don't delete event v2\n";
			i++;
		}
		static void DelTestResult() {
			if (i == 0)results += "Delete all events of class\n";
			if (!testDelTest2)results += "Delete all events\n";
			i = 0;
			testDelTest2 = false;
		}
	};
	int Test::i = 0;
}

std::string Test2() {
	try {
		Test2Helpers::Test ob1, ob2;
		//tests for starting and closing window
		GF::IOModule::Window window;
		window.ShowAsync();
		std::this_thread::sleep_for(2s);
		window.Close();
		window.Close();
		window.ShowAsync();
		//tests for events' support
		sf::Event ev;
		ev.key.alt = true;
		ev.key.code = GF::IOModule::Keyboard::Dash;
		ev.joystickButton.joystickId = 1;
		ev.joystickMove.axis = GF::IOModule::Joystick::Axis::U;
		ev.joystickMove.position = 132;


		//tests for adding and deleting events' functions
		window.JoystickButtonPress += Test2Helpers::JoystickButtonDelTest;
		window.JoystickButtonPress -= Test2Helpers::JoystickButtonDelTest;
		window.JoystickButtonPress += Test2Helpers::JoystickButtonDelTest2;
		window.JoystickButtonPress += {(Test2Helpers::Test::rzut)&Test2Helpers::Test::JoystickButtonDelTest, &ob1};
		window.JoystickButtonPress += {(Test2Helpers::Test::rzut)&Test2Helpers::Test::JoystickButtonDelTest, &ob2};
		window.JoystickButtonPress -= {(Test2Helpers::Test::rzut)&Test2Helpers::Test::JoystickButtonDelTest, &ob2};
		window.JoystickMove += Test2Helpers::JoystickMoveTest;
#ifdef DEBUG
		window.TestEvents(ev);
#endif
		Test2Helpers::Test::DelTestResult();

		window.JoystickButtonPress.clear();

		window.JoystickButtonPressAsync += Test2Helpers::JoystickButtonDelTest2;
		window.JoystickButtonPress += {(Test2Helpers::Test::rzut)&Test2Helpers::Test::JoystickButtonDelTest, &ob1};
		window.JoystickButtonPress += {(Test2Helpers::Test::rzut)&Test2Helpers::Test::JoystickButtonDelTest, &ob2};
		window.JoystickButtonPress -= {(Test2Helpers::Test::rzut)&Test2Helpers::Test::JoystickButtonDelTest, &ob2};
#ifdef DEBUG
		window.TestEvents(ev);
#endif
		Test2Helpers::Test::DelTestResult();
		std::this_thread::sleep_for(2s);
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