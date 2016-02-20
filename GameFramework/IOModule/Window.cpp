#include "Window.h"

namespace GF {
	namespace IOModule {
		Window::Window()
		{
		}

		Window::~Window()
		{
			settings.opened = false;
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
			mutexGraph.lock();
			window.create(sf::VideoMode(settings.size.x, settings.size.y, 32), settings.title,
				(settings.fullscreen ? sf::Style::Fullscreen : 0) | (settings.hasCloseButton ? sf::Style::Close : 0) |
				(settings.hasTitlebar ? sf::Style::Titlebar : 0) | (settings.canResize ? sf::Style::Resize : 0));
			window.setVerticalSyncEnabled(settings.vsync);
			if (settings.framerate > 0)window.setFramerateLimit(settings.framerate);
			if (settings.joystickThreshold > 0)window.setJoystickThreshold(settings.joystickThreshold);
			window.setMouseCursorVisible(settings.cursorVisible);
			settings.opened = true;
			mutexGraph.unlock();
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
			std::lock_guard<std::mutex> guard(mutexGraph);
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
			std::lock_guard<std::mutex> guard(mutexGraph);
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
			std::lock_guard<std::mutex> guard(mutexGraph);
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
			std::lock_guard<std::mutex> guard(mutexGraph);
			graphObjs.push_back(val);
		}

		void Window::removeGraphObj(Core::MemGuard<GraphObject2D> rem)
		{
			std::lock_guard<std::mutex> guard(mutexGraph);
			for (auto i = graphObjs.begin(); i != graphObjs.end(); i++) {
				if (rem == (*i)) {
					std::swap(i,graphObjs.end());graphObjs.pop_back();
					break;
				}
			}
		}

		void Window::captureToFile(std::string path)
		{
			std::lock_guard<std::mutex> guard(mutexGraph);
			window.display();
			sf::Image im(window.capture());
			if (!im.saveToFile(path))
				throw std::runtime_error("Cannot save to file");

		}

		const std::string & Window::getTitle()
		{
			return settings.title;
		}

		const Size Window::getSize()
		{
			return window.getSize();
		}

		const Pos Window::getPosition()
		{
			return window.getPosition();
		}

#ifdef DEBUG
		void Window::TestEvents(sf::Event &ev)
		{
			Events::EventArgs stdArg;
			OnEvent<Events::EventArgs>(GainedFocus, &GainedFocusAsync, stdArg);
			OnEvent<Events::EventArgs>(LostFocus, &LostFocusAsync, stdArg);
			OnEvent<Events::ResizeArgs>(Resize, &ResizeAsync, ev.size);
			OnEvent<Events::JoystickButtonArgs>(JoystickButtonPressed, &JoystickButtonPressedAsync, ev.joystickButton);
			OnEvent<Events::JoystickButtonArgs>(JoystickButtonRelease, &JoystickButtonReleaseAsync, ev.joystickButton);
			OnEvent<Events::JoystickArgs>(JoystickConnect, &JoystickConnectAsync, ev.joystickConnect);
			OnEvent<Events::JoystickArgs>(JoystickDisconnect, &JoystickDisconnectAsync, ev.joystickConnect);
			OnEvent<Events::JoystickMoveArgs>(JoystickMove, &JoystickMoveAsync, ev.joystickMove);
			onKeyPressed(ev.key);
			onKeyRelease(ev.key);
			onClick(ev.mouseButton);
			onReleaseMouse(ev.mouseButton);
			OnEvent<Events::EventArgs>(MouseEnter, &MouseEnterAsync, stdArg);
			OnEvent<Events::EventArgs>(MouseLeft, &MouseLeftAsync, stdArg);
			OnEvent<Events::MouseWheelArgs>(MouseWheel, &MouseWheelAsync, ev.mouseWheel);
			onTextType(ev.text);
		}
#endif

		void Window::InputLoop()//TODO bad std::function<void(void)>, but already I not have any idea.
		{
			Events::EventArgs stdArg;
			sf::Event ev;
			bool con;

			while (settings.opened && window.isOpen())
			{
				mutexGraph.lock();
				con = window.pollEvent(ev);
				mutexGraph.unlock();
				while(con)// must use var opened because if window was closed after previous condition and before pollEvent program tried call to nullptr object
				{
					switch (ev.type) {
					case sf::Event::EventType::Closed:
						onClose(); break;
					case sf::Event::EventType::GainedFocus:
						OnEvent<Events::EventArgs>(GainedFocus, &GainedFocusAsync, stdArg); break;
					case sf::Event::EventType::LostFocus:
						OnEvent<Events::EventArgs>(LostFocus, &LostFocusAsync, stdArg); break;
					case sf::Event::EventType::Resized:
						OnEvent<Events::ResizeArgs>(Resize, &ResizeAsync, ev.size); break;
					case sf::Event::EventType::JoystickButtonPressed:
						OnEvent<Events::JoystickButtonArgs>(JoystickButtonPressed, &JoystickButtonPressedAsync, ev.joystickButton); break;
					case sf::Event::EventType::JoystickButtonReleased:
						OnEvent<Events::JoystickButtonArgs>(JoystickButtonRelease, &JoystickButtonReleaseAsync, ev.joystickButton); break;
					case sf::Event::EventType::JoystickConnected:
						OnEvent<Events::JoystickArgs>(JoystickConnect, &JoystickConnectAsync, ev.joystickConnect); break;
					case sf::Event::EventType::JoystickDisconnected:
						OnEvent<Events::JoystickArgs>(JoystickDisconnect, &JoystickDisconnectAsync, ev.joystickConnect); break;
					case sf::Event::EventType::JoystickMoved:
						OnEvent<Events::JoystickMoveArgs>(JoystickMove, &JoystickMoveAsync, ev.joystickMove); break;
					case sf::Event::EventType::KeyPressed:
						onKeyPressed(ev.key); break;
					case sf::Event::EventType::KeyReleased:
						onKeyRelease(ev.key); break;
					case sf::Event::EventType::MouseButtonPressed:
						onClick(ev.mouseButton); break;
					case sf::Event::EventType::MouseButtonReleased:
						onReleaseMouse(ev.mouseButton); break;
					case sf::Event::EventType::MouseEntered:
						OnEvent<Events::EventArgs>(MouseEnter, &MouseEnterAsync, stdArg); break;
					case sf::Event::EventType::MouseLeft:
						OnEvent<Events::EventArgs>(MouseLeft, &MouseLeftAsync, stdArg); break;
					case sf::Event::EventType::MouseMoved:
						onMouseMove(ev.mouseMove); break;
					case sf::Event::EventType::MouseWheelScrolled:
						OnEvent<Events::MouseWheelArgs>(MouseWheel, &MouseWheelAsync, ev.mouseWheel); break;
					case sf::Event::EventType::TextEntered:
						onTextType(ev.text); break;
					}
					mutexGraph.lock();
					con = window.pollEvent(ev);
					mutexGraph.unlock();
				};
				onWindowRender();
			}
		}

		void Window::onWindowRender()
		{
			if (settings.opened && window.isOpen()) {
				
				Events::EventArgs args;
				OnEvent<Events::EventArgs>(Render, &RenderAsync, args);
				window.clear();
				std::lock_guard<std::mutex> guard(mutexGraph);
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
			settings.opened = false;
			Events::EventArgs args;
			std::lock_guard<std::mutex> guard(mutexGraph);
			if (window.isOpen()) {
				args.cancel = false;
				OnEvent<Events::EventArgs>(WindowClose, nullptr, args);
			}
			if (!args.cancel && window.isOpen()) {
				window.close();
			}
		}

		void Window::onClick(Events::MouseButtonArgs args)
		{
			if (clickableElements) {
				std::lock_guard<std::mutex> guard(mutexGraph);
				Core::MemGuard<GraphObject2D> lastFocus = focusedItem;
				Events::EventArgs stdArgs;
				draggedItem = focusedItem = nullptr;
				Posf pos = { static_cast<float>(args.x), static_cast<float>(args.y) };
				for (auto el = graphObjs.rbegin(); el != graphObjs.rend(); el++) {
					if ((*el)->checkClicked(pos)) {
						draggedItem = (*el);
						focusedItem = (*el);
						if (focusedItem != lastFocus) {
							if(focusedItem!=nullptr)
								focusedItem->onGainedFocus(stdArgs);
						}
						else lastFocus = nullptr;
						break;
					}
				}
				if (lastFocus != nullptr)
					lastFocus->onLostFocus(stdArgs);
			}
			OnEvent(MouseButtonPressed, &MouseButtonPressedAsync, args);
		}

		void Window::onReleaseMouse(Events::MouseButtonArgs args)
		{
			if (draggedItem != nullptr) {
				draggedItem->onMouseRelease(args);
				draggedItem = nullptr;
			}
			OnEvent(MouseButtonRelease, &MouseButtonReleaseAsync, args);
		}

		void Window::onMouseMove(Events::MouseMoveArgs args)
		{
			if (draggedItem != nullptr) {
				draggedItem->onMouseMove(args);
			}
			OnEvent(MouseMove, &MouseMoveAsync, args);
		}

		void Window::onTextType(Events::TextTypeArgs args)
		{
			if (focusedItem != nullptr)
				focusedItem->onTextType(args);
			OnEvent(TextType, &TextTypeAsync, args);
		}

		void Window::onKeyPressed(Events::KeyboardArgs args)
		{
			if (focusedItem != nullptr)
				focusedItem->onKeyPressed(args);
			OnEvent(KeyPressed, &KeyPressedAsync, args);
		}

		void Window::onKeyRelease(Events::KeyboardArgs args)
		{
			if (focusedItem != nullptr)
				focusedItem->onKeyRelease(args);
			OnEvent(KeyRelease, &KeyReleaseAsync, args);
		}

		void Window::setTitle(const std::string title)
		{
			if (title.size() > 0) {
				
				settings.title = title;
				if (window.isOpen()) window.setTitle(title);
			}
		}

		void Window::setSize(const Size size)
		{
			if (size.x >= MIN_SIZE.x&&size.y > MIN_SIZE.y) {
				
				settings.size = size;
				if (window.isOpen())
					window.setSize(size);
			}
		}

		void Window::setPosition(const Pos pos)
		{
			
			settings.pos = pos;
			window.setPosition(pos);
		}

		void Window::setCursorVisible(bool flag)
		{
			
			settings.cursorVisible = flag;
			window.setMouseCursorVisible(flag);
		}

		void Window::setVerticalSyncEnabled(bool enabled)
		{
			
			settings.vsync = enabled;
			window.setVerticalSyncEnabled(enabled);
		}

		void Window::setKeyRepeatEnabled(bool enabled)
		{
			
			settings.keyRepeatEnabled = enabled;
			window.setKeyRepeatEnabled(enabled);
		}

		void Window::setFramerateLimit(unsigned int limit)
		{
			
			settings.framerate = limit;
			window.setFramerateLimit(limit);
		}

		void Window::setJoystickThreshold(float threshold)
		{
			
			settings.joystickThreshold = threshold;
			window.setJoystickThreshold(threshold);
		}

		void Window::setFullscreen(bool enabled)
		{
			settings.fullscreen = enabled;
		}

		void Window::setCanResize(bool enabled)
		{
			settings.canResize = enabled;
		}

		void Window::setCloseButtonVisible(bool enabled)
		{
			settings.hasCloseButton = enabled;
		}

		void Window::setTitleBarVisible(bool enabled)
		{
			settings.hasTitlebar = enabled;
		}

		void Window::appendCamera(const Camera& cam)
		{
			std::lock_guard<std::mutex> guard(mutexGraph);
			cams.push_back(&cam);
		}

		void Window::removeCamera(const Camera & cam)
		{
			std::lock_guard<std::mutex> guard(mutexGraph);
			for (auto i = cams.begin(); i != cams.end(); i++) {
				if (const_cast<Camera*>(&cam) == (*i)) {
					std::swap(i,cams.end());cams.pop_back();
					break;
				}
			}
		}

		void Window::clearCameras()
		{
			std::lock_guard<std::mutex> guard(mutexGraph);
			cams.clear();
		}

		void Window::clearGraphObjs()
		{
			std::lock_guard<std::mutex> guard(mutexGraph);
			graphObjs.clear();
		}

	}
}