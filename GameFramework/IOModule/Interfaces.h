#pragma once
#include "EventArgs.hpp"
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
			std::shared_ptr<ITimer> CreateTimer();
			void AppendGraphObj(std::shared_ptr<IGraphObject2D>);
			void AppendTimer(std::shared_ptr<ITimer>);
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
		};

	}
}