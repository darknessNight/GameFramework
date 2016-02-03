#pragma once
#include "../stdafx.h"
#include "SFML\Graphics.hpp"

void Test1() {
	std::clog << "Test1";
	sf::RenderWindow okno(sf::VideoMode(320, 240), "Test1");
	sf::Clock stoper;
	while (okno.isOpen())
	{
		sf::Event event;
		while (okno.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				okno.close();

		}
		okno.clear();

		sf::CircleShape ksztalt(std::sin(stoper.getElapsedTime().asSeconds()) * okno.getSize().y / 8 + okno.getSize().y / 4);
		ksztalt.setOrigin(sf::Vector2f(ksztalt.getRadius(), ksztalt.getRadius()));
		ksztalt.setPosition(okno.getSize().x / 2.0f, okno.getSize().y / 2.0f);
		ksztalt.setFillColor(sf::Color::Yellow);
		okno.draw(ksztalt);

		okno.display();
	}
}