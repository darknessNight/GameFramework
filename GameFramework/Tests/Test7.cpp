#pragma once
#include "../IOModule/Window.h"
#include "../IOModule/Sound.h"

std::string Test7() {
	std::string result;
	using namespace GF::IOModule;
	using namespace std::literals;
	char ret;
	
	Window window;
	window.setSize({ 1024,576 });
	window.Show();


	std::clog << "Do you hear three songs?(Y/N)\n";
	std::cin >> ret;
	if (ret != 'y'&& ret != 'Y') {
		result += "Playing not working";
	}

	return result;
}