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
			window.create(sf::VideoMode(size.x, size.y, 32), title);
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

#ifdef DEBUG
		void Window::TestEvents(sf::Event ev)
		{
			Events::EventArgs stdArg;
			OnEvent<Events::EventArgs>(WindowFocused, &WindowFocusedAsync, stdArg);
			OnEvent<Events::EventArgs>(WindowLostFocus, &WindowLostFocusAsync, stdArg);
			OnEvent<Events::ResizeArgs>(WindowResize, &WindowResizeAsync, ev.size);
			OnEvent<Events::JoystickButtArgs>(JoystickButtonPress, &JoystickButtonPressAsync, ev.joystickButton);
			OnEvent<Events::JoystickButtArgs>(JoystickButtonRelease, &JoystickButtonReleaseAsync, ev.joystickButton);
			OnEvent<Events::JoystickArgs>(JoystickConnect, &JoystickConnectAsync, ev.joystickConnect);
			OnEvent<Events::JoystickArgs>(JoystickDisconnect, &JoystickDisconnectAsync, ev.joystickConnect);
			OnEvent<Events::JoystickMoveArgs>(JoystickMove, &JoystickMoveAsync, ev.joystickMove);
			OnEvent<Events::KeyboardArgs>(KeyPress, &KeyPressAsync, ev.key);
			OnEvent<Events::KeyboardArgs>(KeyRelease, &KeyReleaseAsync, ev.key);
			OnEvent<Events::MouseButtArgs>(MouseButtonPress, &MouseButtonPressAsync, ev.mouseButton);
			OnEvent<Events::MouseButtArgs>(MouseButtonRelease, &MouseButtonReleaseAsync, ev.mouseButton);
			OnEvent<Events::EventArgs>(MouseEnter, &MouseEnterAsync, stdArg);
			OnEvent<Events::EventArgs>(MouseLeft, &MouseLeftAsync, stdArg);
			OnEvent<Events::MouseWheelArgs>(MouseWheel, &MouseWheelAsync, ev.mouseWheel);
			OnEvent<Events::TextTypeArgs>(TextType, &TextTypeAsync, ev.text);
		}
#endif

		void Window::InputLoop()//TODO bad function, but already I not have any idea.
		{
			while (window.isOpen())
			{
				Events::EventArgs stdArg;
				sf::Event ev;
				while (window.pollEvent(ev))
				{
					switch (ev.type) {
					case sf::Event::EventType::Closed:
						OnClose(); break;
					case sf::Event::EventType::GainedFocus:
						OnEvent<Events::EventArgs>(WindowFocused, &WindowFocusedAsync, stdArg); break;
					case sf::Event::EventType::LostFocus:
						OnEvent<Events::EventArgs>(WindowLostFocus, &WindowLostFocusAsync, stdArg); break;
					case sf::Event::EventType::Resized:
						OnEvent<Events::ResizeArgs>(WindowResize, &WindowResizeAsync, ev.size); break;
					case sf::Event::EventType::JoystickButtonPressed:
						OnEvent<Events::JoystickButtArgs>(JoystickButtonPress, &JoystickButtonPressAsync, ev.joystickButton); break;
					case sf::Event::EventType::JoystickButtonReleased:
						OnEvent<Events::JoystickButtArgs>(JoystickButtonRelease, &JoystickButtonReleaseAsync, ev.joystickButton); break;
					case sf::Event::EventType::JoystickConnected:
						OnEvent<Events::JoystickArgs>(JoystickConnect, &JoystickConnectAsync, ev.joystickConnect); break;
					case sf::Event::EventType::JoystickDisconnected:
						OnEvent<Events::JoystickArgs>(JoystickDisconnect, &JoystickDisconnectAsync, ev.joystickConnect); break;
					case sf::Event::EventType::JoystickMoved:
						OnEvent<Events::JoystickMoveArgs>(JoystickMove, &JoystickMoveAsync, ev.joystickMove); break;
					case sf::Event::EventType::KeyPressed:
						OnEvent<Events::KeyboardArgs>(KeyPress, &KeyPressAsync, ev.key); break;
					case sf::Event::EventType::KeyReleased:
						OnEvent<Events::KeyboardArgs>(KeyRelease, &KeyReleaseAsync, ev.key); break;
					case sf::Event::EventType::MouseButtonPressed:
						OnEvent<Events::MouseButtArgs>(MouseButtonPress, &MouseButtonPressAsync, ev.mouseButton); break;
					case sf::Event::EventType::MouseButtonReleased:
						OnEvent<Events::MouseButtArgs>(MouseButtonRelease, &MouseButtonReleaseAsync, ev.mouseButton); break;
					case sf::Event::EventType::MouseEntered:
						OnEvent<Events::EventArgs>(MouseEnter, &MouseEnterAsync, stdArg); break;
					case sf::Event::EventType::MouseLeft:
						OnEvent<Events::EventArgs>(MouseLeft, &MouseLeftAsync, stdArg); break;
					case sf::Event::EventType::MouseMoved:
					case sf::Event::EventType::MouseWheelScrolled:
						OnEvent<Events::MouseWheelArgs>(MouseWheel, &MouseWheelAsync, ev.mouseWheel); break;
					case sf::Event::EventType::TextEntered:
						OnEvent<Events::TextTypeArgs>(TextType, &TextTypeAsync, ev.text); break;
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
			args.cancel = false;
			OnEvent<Events::EventArgs>(WindowClose, nullptr, args);
			if (!args.cancel && window.isOpen())
				window.close();
		}

		void Window::setTitle(const std::string title)
		{
			if (title.size() > 0) {
				this->title = title;
				if (window.isOpen()) window.setTitle(title);
			}
		}

		void Window::setSize(const Size size)
		{
			if (size.x >= MIN_SIZE.x&&size.y > MIN_SIZE.y) {
				this->size = size;
				if(window.isOpen())
				window.setSize(size);
			}
		}

		void Window::setPosition(const Position pos)
		{
			this->pos = pos;
			window.setPosition(pos);
		}

		void Window::setCursorVisible(bool flag)
		{
			window.setMouseCursorVisible(flag);
		}

		void Window::setVerticalSyncEnabled(bool enabled)
		{
			window.setVerticalSyncEnabled(enabled);
		}

		void Window::setKeyRepeatEnabled(bool enabled)
		{
			window.setKeyRepeatEnabled(enabled);
		}

		void Window::setFramerateLimit(unsigned int limit)
		{
			window.setFramerateLimit(limit);
		}

		void Window::setJoystickThreshold(float threshold)
		{
			window.setJoystickThreshold(threshold);
		}

}
}