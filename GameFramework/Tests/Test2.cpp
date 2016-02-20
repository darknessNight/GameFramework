/*Checking basic event support
*/
#pragma once
#include "../../GameFramework/stdafx.h"
#include "../../GameFramework/IOModule/Window.h"
#include "Tests.h"

std::string Test2();
AutoAdd AA2(Test2, "IOModule", "Events Test");

using namespace GF::IOModule::Events;
using namespace std::literals;
namespace Test2Helpers {
	std::string results;
	bool testDelTest2 = false;

	void JoystickButtonDelTest(GF::IOModule::Events::JoystickButtonArgs &args) {
		results += "Don't delete event\n";
	}

	void JoystickButtonDelTest2(GF::IOModule::Events::JoystickButtonArgs &args) {
		testDelTest2 = true;
	}

	void JoystickMoveTest(GF::IOModule::Events::JoystickMoveArgs &args) {
		if (args.axis != GF::IOModule::Joystick::Axis::U || args.joystickId != 1 || args.position != 132)
			results += "Error of args\n";
	}

	class Test :public GF::Core::Object {
	public:
		typedef void(Object::*rzut)(JoystickButtonArgs&);
		static int i;
		void JoystickButtonDelTest(GF::IOModule::Events::JoystickButtonArgs &args) {
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


		//tests for adding and deleting events' std::function<void(void)>s
		window.JoystickButtonPressed += Test2Helpers::JoystickButtonDelTest;
		window.JoystickButtonPressed -= Test2Helpers::JoystickButtonDelTest;
		window.JoystickButtonPressed += Test2Helpers::JoystickButtonDelTest2;
		window.JoystickButtonPressed += {(Test2Helpers::Test::rzut)&Test2Helpers::Test::JoystickButtonDelTest, &ob1};
		window.JoystickButtonPressed += {(Test2Helpers::Test::rzut)&Test2Helpers::Test::JoystickButtonDelTest, &ob2};
		window.JoystickButtonPressed -= {(Test2Helpers::Test::rzut)&Test2Helpers::Test::JoystickButtonDelTest, &ob2};
		window.JoystickMove += Test2Helpers::JoystickMoveTest;

		window.TestEvents(ev);

		Test2Helpers::Test::DelTestResult();

		window.JoystickButtonPressed.clear();

		window.JoystickButtonPressedAsync += Test2Helpers::JoystickButtonDelTest2;
		window.JoystickButtonPressed += {(Test2Helpers::Test::rzut)&Test2Helpers::Test::JoystickButtonDelTest, &ob1};
		window.JoystickButtonPressed += {(Test2Helpers::Test::rzut)&Test2Helpers::Test::JoystickButtonDelTest, &ob2};
		window.JoystickButtonPressed -= {(Test2Helpers::Test::rzut)&Test2Helpers::Test::JoystickButtonDelTest, &ob2};

		window.TestEvents(ev);

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
