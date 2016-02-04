#include "Window.h"

namespace GameFramework {
	namespace IOModule {
		Window::Window()
		{
		}

		Window::~Window()
		{
			if (thread != nullptr && thread->joinable())
				thread->join();
			if (window.isOpen())
				window.close();
		}

		void Window::Show()
		{
			if (thread != nullptr && std::this_thread::get_id() != thread->get_id() && thread->joinable()) thread->join();
			window.create(sf::VideoMode(800, 600, 32), "Test2");
			window.setFramerateLimit(60);
			InputLoop();
		}

		void Window::ShowAsync()
		{
			if (thread != nullptr && thread->joinable()) thread->join();
			thread = std::shared_ptr<std::thread>(new std::thread(&Window::Show, this));
		}

		void Window::Close()
		{
			OnClose();
		}

		void Window::InputLoop()
		{
			while (window.isOpen())
			{
				sf::Event ev;
				while (window.pollEvent(ev))
				{
					switch (ev.type) {
					case sf::Event::EventType::KeyPressed:
						
					case sf::Event::Closed:

						window.close();
					}

				}
				window.display();
			}
		}

		void Window::OnWindowRender()
		{
			Events::EventArgs args;
			OnEvent<Events::EventArgs>(WindowRender, &WindowRenderAsync, args);
		}

		void Window::OnClose()
		{
			Events::EventArgs args;
			OnEvent<Events::EventArgs>(WindowClose, nullptr, args);
			if (!args.cancel && window.isOpen())
				window.close();
		}

	}
}