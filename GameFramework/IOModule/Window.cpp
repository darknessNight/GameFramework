#include "Window.h"

namespace RPGFramework {
	namespace IOModule {
		void Window::Show()
		{
			window.create(sf::VideoMode(800, 600, 32), "Test2");
			window.setFramerateLimit(60);
			InputLoop();
		}

		void Window::ShowAsync()
		{
		}

		void Window::Close()
		{
		}

		void Window::InputLoop()
		{
			while (window.isOpen())
			{
				sf::Event ev;
				while (window.pollEvent(ev))
				{
					switch (ev.type) {
					case sf::Event::KeyPressed:
						if (ev.key.code != sf::Keyboard::Escape) continue;
					case sf::Event::Closed:
						window.close();
					}

				}
				window.display();
			}
		}

	}
}