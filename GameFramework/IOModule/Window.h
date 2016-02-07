/*
Window class.
INFO
framerate and vsync doesn't work after call inputLoop. This options must be changed before create window or after change
window must be recreated
*/
#pragma once
#include "../stdafx.h"
#include "Texture.h"

namespace GF {
	namespace IOModule {
		class Window :NonCopyable, public AWindow {
		public:
			Window();
			~Window();
			void Show();
			void ShowAsync();
			void Close();
			std::shared_ptr<Texture2D> CreateTexture(Size size, int z_index=-1);
			std::shared_ptr<ITimer> CreateTimer();
			void AppendGraphObj(std::shared_ptr<GraphObject2D>, int z_index);
			void AppendGraphObj(std::shared_ptr<IGraphObject2D>);
			void removeGraphObj(const std::shared_ptr<IGraphObject2D>);
			void AppendTimer(std::shared_ptr<ITimer>);
			void captureToFile(std::string path);
			//properties
			const std::string& getTitle() { return title; }
			const Size& getSize() { return size; }
			const Pos& getPosition() { return pos; }
			void setTitle(const std::string title);
			void setSize(const Size size);
			void setPosition(const Pos pos);
			void setCursorVisible(bool flag);
			void setVerticalSyncEnabled(bool enabled);
			void setKeyRepeatEnabled(bool enabled);
			void setFramerateLimit(unsigned int limit);
			void setJoystickThreshold(float threshold);
			void setFullscreen(bool enabled);
			void setCanResize(bool enabled);
			void setCloseButtonVisible(bool enabled);
			void setTitleBarVisible(bool enabled);

			void clearGraphObjs();
#ifdef DEBUG
			void TestEvents(sf::Event &ev);
#endif // DEBUG

		protected:
			void InputLoop();
#pragma region OnEvent Funcs
			void onWindowRender();
			void onClose();
			void onClick();//TODO
			template <typename ArgType> void OnEvent(Events::Event<ArgType> &sync, Events::Event<ArgType>* async, ArgType args);
#pragma endregion
		public:
#pragma region Events
			Events::Event<Events::EventArgs> WindowRender;
			Events::Event<Events::ResizeArgs> WindowResize;
			Events::Event<Events::EventArgs> WindowFocused;
			Events::Event<Events::EventArgs> WindowLostFocus;
			Events::Event<Events::EventArgs> WindowClose;
			Events::Event<Events::KeyboardArgs> KeyPress;
			Events::Event<Events::KeyboardArgs> KeyRelease;
			Events::Event<Events::MouseButtArgs> MouseButtonPress;
			Events::Event<Events::MouseButtArgs> MouseButtonRelease;
			Events::Event<Events::MouseMoveArgs> MouseMove;
			Events::Event<Events::MouseWheelArgs> MouseWheel;
			Events::Event<Events::EventArgs> MouseLeft;
			Events::Event<Events::EventArgs> MouseEnter;
			Events::Event<Events::JoystickButtArgs> JoystickButtonPress;
			Events::Event<Events::JoystickButtArgs> JoystickButtonRelease;
			Events::Event<Events::JoystickMoveArgs> JoystickMove;
			Events::Event<Events::JoystickArgs> JoystickConnect;
			Events::Event<Events::JoystickArgs> JoystickDisconnect;
			Events::Event<Events::TextTypeArgs> TextType;
			//async events
			Events::Event<Events::EventArgs> WindowRenderAsync;
			Events::Event<Events::ResizeArgs> WindowResizeAsync;
			Events::Event<Events::EventArgs> WindowFocusedAsync;
			Events::Event<Events::EventArgs> WindowLostFocusAsync;
			Events::Event<Events::KeyboardArgs> KeyPressAsync;
			Events::Event<Events::KeyboardArgs> KeyReleaseAsync;
			Events::Event<Events::MouseButtArgs> MouseButtonPressAsync;
			Events::Event<Events::MouseButtArgs> MouseButtonReleaseAsync;
			Events::Event<Events::MouseMoveArgs> MouseMoveAsync;
			Events::Event<Events::MouseWheelArgs> MouseWheelAsync;
			Events::Event<Events::EventArgs> MouseLeftAsync;
			Events::Event<Events::EventArgs> MouseEnterAsync;
			Events::Event<Events::JoystickButtArgs> JoystickButtonPressAsync;
			Events::Event<Events::JoystickButtArgs> JoystickButtonReleaseAsync;
			Events::Event<Events::JoystickMoveArgs> JoystickMoveAsync;
			Events::Event<Events::JoystickArgs> JoystickConnectAsync;
			Events::Event<Events::JoystickArgs> JoystickDisconnectAsync;
			Events::Event<Events::TextTypeArgs> TextTypeAsync;
#pragma endregion
		protected:
			std::mutex mutex;
			bool fullscreen = false;
			bool canResize = false;
			bool hasCloseButton = true;
			bool hasTitlebar = true;
			unsigned framerate = 0;
			bool vsync = false;
			bool opened=false;
			bool keyRepeatEnabled = true;
			bool cursorVisible = true;
			float joystickThreshold=-1;
			std::string title = "Window";
			Pos pos = { 0,0 };
			Size size = { 800,600 };
			std::shared_ptr<std::thread> thread;
			sf::RenderWindow window;
			std::vector<std::shared_ptr<GraphObject2D>> graphObjs;
			//consts
			const Size MIN_SIZE = { 10,10 };
		};


		template<typename ArgType>
		inline void Window::OnEvent(Events::Event<ArgType>& sync, Events::Event<ArgType>* async, ArgType args)
		{
			if (async != nullptr && async->size() > 0) {
				std::thread t(&Events::Event<ArgType>::operator(), async, this, args);
				t.detach();//TODO to niehumanitarne porzucaæ w¹tki. Do naprawy
			}
			sync(this, args);
		}
	}
}