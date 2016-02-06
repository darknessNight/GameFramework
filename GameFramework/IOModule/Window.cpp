#include "Window.h"

namespace GF {
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
			window.create(sf::VideoMode(size.x, size.y, 32), title,
				(fullscreen ? sf::Style::Fullscreen : 0) | (hasCloseButton ? sf::Style::Close : 0) |
				(hasTitlebar ? sf::Style::Titlebar : 0) | (canResize ? sf::Style::Resize : 0));
			window.setVerticalSyncEnabled(vsync);
			if (framerate > 0)window.setFramerateLimit(framerate);
			if (joystickThreshold > 0)window.setJoystickThreshold(joystickThreshold);
			window.setMouseCursorVisible(cursorVisible);
			opened = true;
			InputLoop();
		}

		void Window::ShowAsync()
		{
			if (thread != nullptr && thread->joinable()) thread->join();
			thread = std::shared_ptr<std::thread>(new std::thread(&Window::Show, this));
		}

		void Window::Close()
		{
			onClose();
		}

		std::shared_ptr<Texture2D> Window::CreateTexture(Size size, int z_index)
		{
			std::shared_ptr<Texture2D> tex(new Texture2D(size));
			AppendGraphObj(tex, z_index);
			return tex;
		}

		std::shared_ptr<ITimer> Window::CreateTimer()
		{
			//TODO
			return std::shared_ptr<ITimer>();
		}

		void Window::AppendGraphObj(std::shared_ptr<GraphObject2D> tex, int z_index)
		{
			if (z_index < 0 || z_index >= graphObjs.size())
				graphObjs.push_back(tex);
			else {
				auto i = graphObjs.begin();
				i += z_index;
				i = graphObjs.insert(i, tex);
			}
		}

		void Window::AppendGraphObj(std::shared_ptr<IGraphObject2D> val)
		{
			std::shared_ptr<GraphObject2D> ptr((GraphObject2D*)val.get());
			graphObjs.push_back(ptr);
		}

		void Window::removeGraphObj(const std::shared_ptr<IGraphObject2D> rem)
		{
			for (auto i = graphObjs.begin(); i != graphObjs.end(); i++) {
				if ((*i) == rem) {
					i = graphObjs.erase(i);
					break;
				}
			}
		}

		void Window::AppendTimer(std::shared_ptr<ITimer>)
		{
			//TODO
		}

		void Window::captureToFile(std::string path)
		{
			window.display();
			sf::Image im(window.capture());
			if (!im.saveToFile(path))
				throw std::exception("Cannot save to file");

		}

#ifdef DEBUG
		void Window::TestEvents(sf::Event &ev)
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
			Events::EventArgs stdArg;
			sf::Event ev;
			while (window.isOpen())
			{
				while (opened && window.pollEvent(ev))// must use var opened because if window was closed after previous condition and before pollEvent program tried call to nullptr object
				{
					switch (ev.type) {
					case sf::Event::EventType::Closed:
						onClose(); break;
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
				onWindowRender();
			}
		}

		void Window::onWindowRender()
		{
			if (opened && window.isOpen()) {
				Events::EventArgs args;
				OnEvent<Events::EventArgs>(WindowRender, &WindowRenderAsync, args);
				window.clear();
				for (auto i = graphObjs.begin(); i != graphObjs.end(); i++)
				{
					(*i)->render(&window);
				}
				window.display();
			}
		}

		void Window::onClose()
		{
			opened = false;
			Events::EventArgs args;
			if (window.isOpen()) {
				args.cancel = false;
				OnEvent<Events::EventArgs>(WindowClose, nullptr, args);
			}
			if (!args.cancel && window.isOpen())
				window.close();

		}

		void Window::onClick()
		{
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
				if (window.isOpen())
					window.setSize(size);
			}
		}

		void Window::setPosition(const Pos pos)
		{
			this->pos = pos;
			window.setPosition(pos);
		}

		void Window::setCursorVisible(bool flag)
		{
			cursorVisible = flag;
			window.setMouseCursorVisible(flag);
		}

		void Window::setVerticalSyncEnabled(bool enabled)
		{
			vsync = enabled;
			window.setVerticalSyncEnabled(enabled);
		}

		void Window::setKeyRepeatEnabled(bool enabled)
		{
			keyRepeatEnabled = enabled;
			window.setKeyRepeatEnabled(enabled);
		}

		void Window::setFramerateLimit(unsigned int limit)
		{
			framerate = limit;
			window.setFramerateLimit(limit);
		}

		void Window::setJoystickThreshold(float threshold)
		{
			joystickThreshold = threshold;
			window.setJoystickThreshold(threshold);
		}

		void Window::setFullscreen(bool enabled)
		{
			fullscreen = enabled;
		}

		void Window::setCanResize(bool enabled)
		{
			canResize = enabled;
		}

		void Window::setCloseButtonVisible(bool enabled)
		{
			hasCloseButton = enabled;
		}

		void Window::setTitleBarVisible(bool enabled)
		{
			hasTitlebar = enabled;
		}

	}
}