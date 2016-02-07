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

		class Window :NonCopyable, public AWindow {
		public:
			Window();
			~Window();
			void Show();
			void ShowAsync();
			void Close();
			Core::MemGuard<Texture2D> CreateTexture(Size size, int z_index=-1);
			Core::MemGuard<Image> CreateImage(Size size, int z_index = -1);
			//ITimer& CreateTimer();
			void AppendGraphObj(Core::MemGuard<GraphObject2D>, int z_index);
			void AppendGraphObj(Core::MemGuard<GraphObject2D>);
			void removeGraphObj(GraphObject2D&);
			//void AppendTimer(ITimer&);
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
			void setCamera(const Camera& cam);

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
			template <typename ArgType> void OnEvent(Core::Events::Event<ArgType> &sync, Core::Events::Event<ArgType>* async, ArgType args);
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
			std::thread* thread;
			sf::RenderWindow window;
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