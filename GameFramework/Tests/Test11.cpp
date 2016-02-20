/*
Test obs³ugi menu
*/

#pragma once
#include "../../GameFramework/Controller/Menu.h"
#include "../../GameFramework/IOModule/Window.h"

#include "Tests.h"
std::string Test11();
AutoAdd AA11(Test11, "Controller", "Menu Controls Test");

namespace Test11Helpers {
	using namespace GF::IOModule;
	int flag = 0;
	void Btn1Click(Events::MouseButtonArgs &args) {
		flag = 1;
	}

	void Btn2Click(Events::MouseButtonArgs &args) {
		flag = 2;
	}

	void ControlGetFocus(Events::EventArgs &args) {
		flag = 1;
	}

	void ControlLostFocus(Events::EventArgs &args) {
		flag = 2;
	}

	std::chrono::time_point<std::chrono::steady_clock> start= std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> render;
	int frameCount = 0;
	typedef std::chrono::duration<double, std::micro> timeDur;
	typedef std::chrono::duration<double, std::milli> timeDur2;
	void FPS(GF::IOModule::Events::EventArgs& arg) {
		if (frameCount >= 100) {
			render = std::chrono::high_resolution_clock::now();
			system("cls");
			std::clog << std::chrono::duration_cast<timeDur>(render - start).count() / 100.0 << "\n"
				<< 100.0 / std::chrono::duration_cast<timeDur2>(render - start).count() * 1000;
			start = render;
			frameCount = 0;
		}
		else frameCount++;
	}
}


std::string Test11() {
	using namespace Test11Helpers;
	using namespace GF;
	using namespace GF::IOModule;
	using namespace GF::Core;
	using namespace GF::Controller::Controls;
	using namespace std::literals;
	std::string result;
	char ret;

	try {
		Window window;
		window.Render += FPS;
		window.clickableElements = true;
		Button btn1(Size({ 100, 30 }));
		btn1.setPosition(200, 200);
		btn1.setVisible(true);
		btn1.setText(L"Button1 Button1");
		btn1.MousePress += Btn1Click;
		Button btn2(100, 30);
		btn2.setPosition(250, 210);
		btn2.setVisible(true);
		btn2.setText(L"Button2");
		btn2.MousePress += Btn2Click;
		btn2.setActiveBackColor(Color::Black);
		btn2.setActiveForeColor(Color::White);
		btn2.setActiveBorderColor(Color(255, 255, 255, 200));

		Button btn3(100, 30);
		btn3.setPosition(450, 210);
		btn3.setVisible(true);
		btn3.setText(L"Button3");
		btn3.setBackColor(Color::Transparent);
		btn3.setBorderSize(0);
		SharedTexture t1, t2;
		t1.loadFromFile("./Tests/Resources/btn1.png");
		t2.loadFromFile("./Tests/Resources/btn2.png");
		btn3.setBackTexture(t1);
		btn3.setActiveBackTexture(t2);


		Textbox tb1(200, 130);
		tb1.setPosition(10, 10);
		tb1.setVisible();
		tb1.GainedFocus += ControlGetFocus;
		tb1.LostFocus += ControlLostFocus;

		Image im1({ 800,600 });
		im1.clear(Color::White);
		im1.setVisible();

		Progressbar pb1(150, 20);
		pb1.setVisible();
		pb1.setPosition(400, 50);
		pb1.setCurrent(23.45f);

		Trackbar trb1(150, 20);
		trb1.setVisible();
		trb1.setPosition(400, 80);

		ProgressbarH pbh1(20, 150);
		pbh1.setVisible();
		pbh1.setPosition(600, 50);
		pbh1.setCurrent(23.45f);

		TrackbarH trbh1(20, 150);
		trbh1.setVisible();
		trbh1.setPosition(650, 50);

		Label l1(100, 10), l2(100, 10);
		l1.setFontSize(15);
		l1.setText(L"Progressbar");
		l1.setPosition(300, 50);
		l2.setFontSize(15);
		l2.setText(L"Trackbar");
		l2.setPosition(300, 80);

		Checkbox cb1(150, 20);
		cb1.setPosition(100, 400);
		cb1.setText(L"Checkbox");
		cb1.setVisible();

		Radiobutton rb1(100,20), rb2(100,20), rb3(100,20);
		rb1.setText(L"Yes");
		rb2.setText(L"No");
		rb3.setText(L"What?");
		rb3.setChecked(true);
		rb1.setPosition(100, 500);
		rb2.setPosition(200, 500);
		rb3.setPosition(300, 500);
		rb1.setVisible();
		rb2.setVisible();
		rb3.setVisible();
		rb2.addToGroup(rb1.getGroup());
		rb3.addToGroup(rb1.getGroup());

		window.appendGraphObj(im1);
		window.appendGraphObj(btn1);
		window.appendGraphObj(btn2);
		window.appendGraphObj(btn3);
		window.appendGraphObj(tb1);
		window.appendGraphObj(pb1);
		window.appendGraphObj(trb1);
		window.appendGraphObj(pbh1);
		window.appendGraphObj(trbh1);
		window.appendGraphObj(l1);
		window.appendGraphObj(l2);
		window.appendGraphObj(cb1);
		window.appendGraphObj(rb1);
		window.appendGraphObj(rb2);
		window.appendGraphObj(rb3);

		window.ShowAsync();
		std::this_thread::sleep_for(1s);
		window.Close();

		sf::Event ev;
		ev.mouseButton.x = 255;
		ev.mouseButton.y = 215;

		flag = 0;
		window.TestEvents(ev);
		if (flag == 0) result += "Event not send\n";
		if (flag == 1) result += "Event send to wrong button\n";

		ev.mouseButton.x = 245;
		ev.mouseButton.y = 215;

		flag = 0;
		window.TestEvents(ev);
		if (flag == 0) result += "Event not send\n";
		if (flag != 1) result += "Event send to wrong button\n";

		ev.mouseButton.x = 11;
		ev.mouseButton.y = 11;
		ev.text.unicode = L'E';

		flag = 0;
		window.TestEvents(ev);
		if (flag == 0) result += "Event not send\n";
		if (flag != 1) result += "Event send to wrong button\n";
		if (tb1.getText() != L"E")result += "Event text is wrong\n";
		tb1.allowNewLine = true;

		ev.mouseButton.x = trb1.getPosition().x+20;
		ev.mouseButton.y = trb1.getPosition().y + 2;

		window.TestEvents(ev);
		if(trb1.getCurrent()!=20.0f/trb1.getSize().x*100)result += "Trackbar doesn't work correctly. Return value: "+std::to_string(trb1.getCurrent())+" is not "+std::to_string(20.0f/trb1.getSize().x*100 )+"\n";

		ev.mouseButton.x = trbh1.getPosition().x + 2;
		ev.mouseButton.y = trbh1.getPosition().y + 20;

		window.TestEvents(ev);
		if (trbh1.getCurrent() != 20.0f / trbh1.getSize().y * 100)result += "TrackbarH doesn't work correctly.\n";


		cb1.setChecked(false);
		ev.mouseButton.x = cb1.getPosition().x + 2;
		ev.mouseButton.y = cb1.getPosition().y + 2;

		window.TestEvents(ev);
		if (!cb1.getChecked())result += "Checkbox doesn't work correctly.\n";

		rb1.setChecked();
		rb2.setChecked(false);
		rb3.setChecked(false);
		ev.mouseButton.x = rb2.getPosition().x + rb2.getSize().x/2;
		ev.mouseButton.y = rb2.getPosition().y;

		window.TestEvents(ev);
		if (!rb2.getChecked())result += "Radiobutton not checked.\n";
		if (rb1.getChecked())result += "Radiobutton not unchecked.\n";


		window.Show();


		system("cls");
		std::clog << "Do you see all controls: 1 Textbox, 2 TextLabels, 2 Progressbar (Horizontal and Vertical), 2 Trackbar  (Horizontal and Vertical), 3 Buttons (one with image), 1 checkbox, 3 radiobuttons?(Y/N)";
		std::cin >> ret;
		if (ret != 'Y' && ret != 'y') result += "Don't display all elements\n";

	}
	catch (std::exception e) {
		result += "Catched error: " + std::string(e.what());
	}

	return result;
}