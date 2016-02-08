#include "Window.h"
#include "../stdafx.h"

namespace GF {
	namespace IOModule {
		Window::Window()
		{
		}

		Window::~Window()
		{
			opened = false;
			clearGraphObjs();
			if (thread != nullptr) {
				if (thread->joinable())
					thread->join();
			}
			if (window.isOpen())
				window.close();
			
		}

		void Window::Show()
		{
			if (thread != nullptr && std::this_thread::get_id() != thread->get_id() && thread->joinable()) thread->join();
			mutex.lock();
			window.create(sf::VideoMode(size.x, size.y, 32), title,
				(fullscreen ? sf::Style::Fullscreen : 0) | (hasCloseButton ? sf::Style::Close : 0) |
				(hasTitlebar ? sf::Style::Titlebar : 0) | (canResize ? sf::Style::Resize : 0));
			window.setVerticalSyncEnabled(vsync);
			if (framerate > 0)window.setFramerateLimit(framerate);
			if (joystickThreshold > 0)window.setJoystickThreshold(joystickThreshold);
			window.setMouseCursorVisible(cursorVisible);
			opened = true;
			mutex.unlock();
			InputLoop();
		}

		void Window::ShowAsync()
		{
			if (thread != nullptr && thread->joinable()) thread->join();
			thread = new std::thread(&Window::Show, this);
		}

		void Window::Close()
		{
			onClose();
		}

		Core::MemGuard<Texture2D> Window::CreateTexture(Size size, int z_index)
		{
			Core::MemGuard<Texture2D> tex;
			tex=new Texture2D(size);
			//std::lock_guard<std::mutex> guard(mutex);
			if (z_index < 0 || z_index >= graphObjs.size()) {
				Core::MemGuard<GraphObject2D> tmp(tex);
				graphObjs.push_back(tmp);
			}
			else {
				auto i = graphObjs.begin();
				i += z_index;
				i = graphObjs.insert(i, tex);
			}
			return tex;
		}

		Core::MemGuard<Image> Window::CreateImage(Size size, int z_index)
		{
			Core::MemGuard<Image> tex;
			tex=new Image(size);
			//std::lock_guard<std::mutex> guard(mutex);
			if (z_index < 0 || z_index >= graphObjs.size())
				graphObjs.push_back(tex);
			else {
				auto i = graphObjs.begin();
				i += z_index;
				i = graphObjs.insert(i, tex);
			}
			return tex;
		}

		void Window::appendGraphObj(Core::MemGuard<GraphObject2D> tex, int z_index)
		{
			//std::lock_guard<std::mutex> guard(mutex);
			if (z_index < 0 || z_index >= graphObjs.size())
				graphObjs.push_back(tex);
			else {
				auto i = graphObjs.begin();
				i += z_index;
				i = graphObjs.insert(i, tex);
			}
		}

		void Window::appendGraphObj(Core::MemGuard<GraphObject2D> val)
		{
			//std::lock_guard<std::mutex> guard(mutex);
			graphObjs.push_back(val);
		}

		void Window::removeGraphObj(Core::MemGuard<GraphObject2D> rem)
		{
			//std::lock_guard<std::mutex> guard(mutex);
			for (auto i = graphObjs.begin(); i != graphObjs.end(); i++) {
				if (rem == (*i)) {
					i = graphObjs.erase(i);
					break;
				}
			}
		}

		void Window::captureToFile(std::string path)
		{
			//std::lock_guard<std::mutex> guard(mutex);
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
			bool con;

			while (opened&&window.isOpen())
			{
				mutex.lock();
				if (opened)
					con = window.pollEvent(ev);
				mutex.unlock();
				while(con)// must use var opened because if window was closed after previous condition and before pollEvent program tried call to nullptr object
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


					mutex.lock();
					if (opened)
						con = window.pollEvent(ev);
					else con = false;
					mutex.unlock();
				};

				onWindowRender();
			}
		}

		void Window::onWindowRender()
		{
			if (opened && window.isOpen()) {
				//std::lock_guard<std::mutex> guard(mutex);
				Events::EventArgs args;
				OnEvent<Events::EventArgs>(WindowRender, &WindowRenderAsync, args);
				window.clear();
				if (cams.size() > 0)
					for each (auto cam in cams)
					{
						window.setView(*cam);
						for (auto i = graphObjs.begin(); i != graphObjs.end(); i++)
						{
							(*i)->render(&window);
						}
					}
				else
					for (auto i = graphObjs.begin(); i != graphObjs.end(); i++)
					{
						(*i)->render(&window);
					}
				window.display();
				window.setView(window.getDefaultView());
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
			if (!args.cancel && window.isOpen()) {
				std::lock_guard<std::mutex> guard(mutex);
				window.close();
			}

		}

		void Window::onClick()
		{
		}

		void Window::setTitle(const std::string title)
		{
			if (title.size() > 0) {
				//std::lock_guard<std::mutex> guard(mutex);
				this->title = title;
				if (window.isOpen()) window.setTitle(title);
			}
		}

		void Window::setSize(const Size size)
		{
			if (size.x >= MIN_SIZE.x&&size.y > MIN_SIZE.y) {
				//std::lock_guard<std::mutex> guard(mutex);
				this->size = size;
				if (window.isOpen())
					window.setSize(size);
			}
		}

		void Window::setPosition(const Pos pos)
		{
			//std::lock_guard<std::mutex> guard(mutex);
			this->pos = pos;
			window.setPosition(pos);
		}

		void Window::setCursorVisible(bool flag)
		{
			//std::lock_guard<std::mutex> guard(mutex);
			cursorVisible = flag;
			window.setMouseCursorVisible(flag);
		}

		void Window::setVerticalSyncEnabled(bool enabled)
		{
			//std::lock_guard<std::mutex> guard(mutex);
			vsync = enabled;
			window.setVerticalSyncEnabled(enabled);
		}

		void Window::setKeyRepeatEnabled(bool enabled)
		{
			//std::lock_guard<std::mutex> guard(mutex);
			keyRepeatEnabled = enabled;
			window.setKeyRepeatEnabled(enabled);
		}

		void Window::setFramerateLimit(unsigned int limit)
		{
			//std::lock_guard<std::mutex> guard(mutex);
			framerate = limit;
			window.setFramerateLimit(limit);
		}

		void Window::setJoystickThreshold(float threshold)
		{
			//std::lock_guard<std::mutex> guard(mutex);
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

		void Window::appendCamera(const Camera& cam)
		{
			cams.push_back(&cam);
		}

		void Window::removeCamera(const Camera & cam)
		{
			for (auto i = cams.begin(); i != cams.end(); i++) {
				if (const_cast<Camera*>(&cam) == (*i)) {
					i = cams.erase(i);
					break;
				}
			}
		}

		void Window::clearCameras()
		{
			cams.clear();
		}

		void Window::clearGraphObjs()
		{
			graphObjs.clear();
		}

	}
}