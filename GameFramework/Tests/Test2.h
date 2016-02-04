#pragma once
#include "../stdafx.h"
#include "../IOModule/Window.h"


std::string Test2() {
	GameFramework::IOModule::Window window;
	window.ShowAsync();
	using namespace std::literals;
	std::this_thread::sleep_for(2s);
	window.Close();
	window.Close();
	window.Show();
	return std::string();
}