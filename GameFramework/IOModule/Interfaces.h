#pragma once
#include <SFML\Graphics.hpp>
#include "EventArgs.hpp"
namespace GF {
	namespace IOModule {
		//TODO zast�pi� typedef interfejsami
		typedef sf::Mouse Mouse;
		typedef sf::Keyboard Keyboard;
		typedef sf::Joystick Joystick;
		typedef sf::NonCopyable NonCopyable;
		typedef sf::Vector2i Pos;
		typedef sf::Vector2f Posf;
		typedef sf::Vector2u Size;
		typedef sf::Vector2f Sizef;
		typedef sf::Color Color;

		__interface IGraphObject2D {
			void setVisible(bool enabled);
			void setPos(const Posf p);
			bool getVisible();
			const Posf& getPos();
			const Sizef& getSize();
			void LoadFromFile(std::string path);
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

		__interface IImage2D:public IGraphObject2D {
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
			bool ApplyGraphObj(std::shared_ptr<IGraphObject2D>);
			bool ApplyTimer(std::shared_ptr<ITimer>);
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