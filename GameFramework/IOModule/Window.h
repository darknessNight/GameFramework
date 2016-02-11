/*
Window class.
INFO
framerate and vsync doesn't work after call inputLoop. This options must be changed before create window or after change
window must be recreated
*/
#pragma once

#include "../stdafx.h"
#include "Texture.h"
#include "Image.h"

namespace GF {
	namespace IOModule {

		struct WindowSettings {
			bool fullscreen = false;
			bool canResize = false;
			bool hasCloseButton = true;
			bool hasTitlebar = true;
			unsigned framerate = 0;
			bool vsync = false;
			bool opened = false;
			bool keyRepeatEnabled = true;
			bool cursorVisible = true;
			float joystickThreshold = -1;
			std::string title = "Window";
			Pos pos = { 0,0 };
			Size size = { 800,600 };
		};

		class Window :NonCopyable{
		public:
			Window();
			~Window();
			void Show();
			void ShowAsync();
			void Close();
			Core::MemGuard<Texture2D> CreateTexture(Size size, int z_index=-1);
			Core::MemGuard<Image> CreateImage(Size size, int z_index = -1);

			void appendGraphObj(Core::MemGuard<GraphObject2D>, int z_index);
			void appendGraphObj(Core::MemGuard<GraphObject2D>);
			void removeGraphObj(Core::MemGuard<GraphObject2D>);
			void clearGraphObjs();

			void appendCamera(const Camera& cam);
			void removeCamera(const Camera& cam);
			void clearCameras();

			void captureToFile(std::string path);
			//properties
			const std::string& getTitle();
			const Size& getSize();
			const Pos& getPosition();
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

#ifdef DEBUG
			void TestEvents(sf::Event &ev);
#endif // DEBUG
		public:
#pragma region Events
			Core::Events::Event<Events::EventArgs> Render;
			   Core::Events::Event<Events::ResizeArgs> Resize;
			   Core::Events::Event<Events::EventArgs> GainedFocus;
			   Core::Events::Event<Events::EventArgs> LostFocus;
			   Core::Events::Event<Events::EventArgs> WindowClose;
			   Core::Events::Event<Events::KeyboardArgs> KeyPressed;
			   Core::Events::Event<Events::KeyboardArgs> KeyRelease;
			   Core::Events::Event<Events::MouseButtonArgs> MouseButtonPressed;
			   Core::Events::Event<Events::MouseButtonArgs> MouseButtonRelease;
			   Core::Events::Event<Events::MouseMoveArgs> MouseMove;
			   Core::Events::Event<Events::MouseWheelArgs> MouseWheel;
			   Core::Events::Event<Events::EventArgs> MouseLeft;
			   Core::Events::Event<Events::EventArgs> MouseEnter;
			   Core::Events::Event<Events::JoystickButtonArgs> JoystickButtonPressed;
			   Core::Events::Event<Events::JoystickButtonArgs> JoystickButtonRelease;
			   Core::Events::Event<Events::JoystickMoveArgs> JoystickMove;
			   Core::Events::Event<Events::JoystickArgs> JoystickConnect;
			   Core::Events::Event<Events::JoystickArgs> JoystickDisconnect;
			   Core::Events::Event<Events::TextTypeArgs> TextType;
			   //async events
			   Core::Events::Event<Events::EventArgs> RenderAsync;
			   Core::Events::Event<Events::ResizeArgs> ResizeAsync;
			   Core::Events::Event<Events::EventArgs> GainedFocusAsync;
			   Core::Events::Event<Events::EventArgs> LostFocusAsync;
			   Core::Events::Event<Events::KeyboardArgs> KeyPressedAsync;
			   Core::Events::Event<Events::KeyboardArgs> KeyReleaseAsync;
			   Core::Events::Event<Events::MouseButtonArgs> MouseButtonPressedAsync;
			   Core::Events::Event<Events::MouseButtonArgs> MouseButtonReleaseAsync;
			   Core::Events::Event<Events::MouseMoveArgs> MouseMoveAsync;
			   Core::Events::Event<Events::MouseWheelArgs> MouseWheelAsync;
			   Core::Events::Event<Events::EventArgs> MouseLeftAsync;
			   Core::Events::Event<Events::EventArgs> MouseEnterAsync;
			   Core::Events::Event<Events::JoystickButtonArgs> JoystickButtonPressedAsync;
			   Core::Events::Event<Events::JoystickButtonArgs> JoystickButtonReleaseAsync;
			   Core::Events::Event<Events::JoystickMoveArgs> JoystickMoveAsync;
			   Core::Events::Event<Events::JoystickArgs> JoystickConnectAsync;
			   Core::Events::Event<Events::JoystickArgs> JoystickDisconnectAsync;
			   Core::Events::Event<Events::TextTypeArgs> TextTypeAsync;
#pragma endregion

		protected:
			void InputLoop();
#pragma region OnEvent Funcs
			void onWindowRender();
			void onClose();
			void onClick(Events::MouseButtonArgs);
			void onReleaseMouse(Events::MouseButtonArgs);
			void onMouseMove(Events::MouseMoveArgs);
			void onTextType(Events::TextTypeArgs);
			void onKeyPressed(Events::KeyboardArgs);
			void onKeyRelease(Events::KeyboardArgs);

			template <typename ArgType> void OnEvent(Core::Events::Event<ArgType> &sync, Core::Events::Event<ArgType>* async, ArgType args);
#pragma endregion
		public:
			bool clickableElements = false;
		protected:
			WindowSettings settings;

			std::mutex mutexGraph;
			Core::MemGuard<std::thread> thread;
			sf::RenderWindow window;

			Core::MemGuard<GraphObject2D> draggedItem;
			Core::MemGuard<GraphObject2D> focusedItem;

			std::vector<Core::MemGuard<GraphObject2D>> graphObjs;
			std::vector<const Camera*> cams;
			//consts
			const Size MIN_SIZE = { 10,10 };
		};


		template<typename ArgType>
		inline void Window::OnEvent(Core::Events::Event<ArgType>& sync, Core::Events::Event<ArgType>* async, ArgType args)
		{
			if (async != nullptr && async->size() > 0) {
				std::thread t(&Core::Events::Event<ArgType>::operator(), async, this, args);
				t.detach();//TODO to niehumanitarne porzucaæ w¹tki. Do naprawy
			}
			sync(this, args);
		}
	}
}