#pragma once
#include "../Core/Events.hpp"
#include "Events.h"
#include "Types.h"

namespace GF {
	namespace IOModule {

		__interface IGraphObject2D {
			void setVisible(bool enabled);
			void setPosition(const Posf p);
			void setColor(const Color c);//change color of object (create color mask)
			void setOrigin(Posf p);
			void setRotation(float angle);//overrive current rotate
			void setScale(float xScale, float yScale);//override current scale
			void setScale(Sizef scale);//override current scale
			bool getVisible();
			const Posf& getPosition();
			const Sizef& getSize();
			const Color& getColor();
			const Posf& getOrigin();
			const float& getRotation();
			const Sizef& getScale();
			void rotate(float angle);//add to current rotate angle
			void scale(float x, float y);//multiple current scale
			void scale(Sizef scale);//multiple current scale
			virtual void loadFromFile(std::string path) = 0;
			void loadFromMemory(const void* mem, unsigned size);
			void loadFromStream(std::istream& stream);
		};

		__interface ITimer {
			/*void setInterval(double miliseconds);
			void start();
			void stop();
			void setFunction(std::function<void(void)>);
			void setAsyncFunction(std::function<void(void)>);*/
		};
		class TimerA:public ITimer{};

		__interface ITexture2D {
		};

		__interface IImage {
			/*void drawLine(Positionf, Positionf, ITexture);
			void drawLine(Positionf, Positionf, Color);
			void drawCircle(Positionf, double r, ITexture);
			void drawCircle(Positionf, double r, Color);
			void drawRegularShape(double r, int corners, ITexture);
			void drawRegularShape(double r, int corners, Color);
			void drawShape(int count, Positionf points[], ITexture);
			void drawShape(int count, Positionf points[], Color);*/
		};
		
		__interface IMultipleGraphObject2D :public IGraphObject2D {

		};

		__interface ICamera2D {
			void MoveTo(const Pos);
			void SetSize(const Size);
		};

		__interface IWindow {
			void Show();
			void ShowAsync();
			void Close();
			//ITimer& CreateTimer();
			//void AppendGraphObj(IGraphObject2D&);
			//void AppendTimer(ITimer&);
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
		};

		class AWindow:public IWindow
		{
		public:
#pragma region Events
			Core::Events::Event<Events::EventArgs> WindowRender;
			Core::Events::Event<Events::ResizeArgs> WindowResize;
			Core::Events::Event<Events::EventArgs> WindowFocused;
			Core::Events::Event<Events::EventArgs> WindowLostFocus;
			Core::Events::Event<Events::EventArgs> WindowClose;
			Core::Events::Event<Events::KeyboardArgs> KeyPress;
			Core::Events::Event<Events::KeyboardArgs> KeyRelease;
			Core::Events::Event<Events::MouseButtArgs> MouseButtonPress;
			Core::Events::Event<Events::MouseButtArgs> MouseButtonRelease;
			Core::Events::Event<Events::MouseMoveArgs> MouseMove;
			Core::Events::Event<Events::MouseWheelArgs> MouseWheel;
			Core::Events::Event<Events::EventArgs> MouseLeft;
			Core::Events::Event<Events::EventArgs> MouseEnter;
			Core::Events::Event<Events::JoystickButtArgs> JoystickButtonPress;
			Core::Events::Event<Events::JoystickButtArgs> JoystickButtonRelease;
			Core::Events::Event<Events::JoystickMoveArgs> JoystickMove;
			Core::Events::Event<Events::JoystickArgs> JoystickConnect;
			Core::Events::Event<Events::JoystickArgs> JoystickDisconnect;
			Core::Events::Event<Events::TextTypeArgs> TextType;
			//async events
			Core::Events::Event<Events::EventArgs> WindowRenderAsync;
			Core::Events::Event<Events::ResizeArgs> WindowResizeAsync;
			Core::Events::Event<Events::EventArgs> WindowFocusedAsync;
			Core::Events::Event<Events::EventArgs> WindowLostFocusAsync;
			Core::Events::Event<Events::KeyboardArgs> KeyPressAsync;
			Core::Events::Event<Events::KeyboardArgs> KeyReleaseAsync;
			Core::Events::Event<Events::MouseButtArgs> MouseButtonPressAsync;
			Core::Events::Event<Events::MouseButtArgs> MouseButtonReleaseAsync;
			Core::Events::Event<Events::MouseMoveArgs> MouseMoveAsync;
			Core::Events::Event<Events::MouseWheelArgs> MouseWheelAsync;
			Core::Events::Event<Events::EventArgs> MouseLeftAsync;
			Core::Events::Event<Events::EventArgs> MouseEnterAsync;
			Core::Events::Event<Events::JoystickButtArgs> JoystickButtonPressAsync;
			Core::Events::Event<Events::JoystickButtArgs> JoystickButtonReleaseAsync;
			Core::Events::Event<Events::JoystickMoveArgs> JoystickMoveAsync;
			Core::Events::Event<Events::JoystickArgs> JoystickConnectAsync;
			Core::Events::Event<Events::JoystickArgs> JoystickDisconnectAsync;
			Core::Events::Event<Events::TextTypeArgs> TextTypeAsync;
#pragma endregion
		};

	}
}