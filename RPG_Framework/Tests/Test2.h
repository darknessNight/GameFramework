#pragma once
#include "../stdafx.h"
#include "../IOModule/Window.h"


std::string Test2() {

	sf::Window oknoAplikacji(sf::VideoMode(800, 600, 32), "Kurs SFML 2.0 - http://cpp0x.pl");
	while (oknoAplikacji.isOpen())
	{
		sf::Event zdarzenie;
		while (oknoAplikacji.pollEvent(zdarzenie))
		{
			if (zdarzenie.type == sf::Event::Closed)
				oknoAplikacji.close();

			if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape)
				oknoAplikacji.close();

			if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Middle)
				oknoAplikacji.close();

		}
		oknoAplikacji.display();
	}

	return std::string();
}