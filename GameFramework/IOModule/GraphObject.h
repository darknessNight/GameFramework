#pragma once
#include "Types.h"
#include "Events.h"
#include "../Core/Events.hpp"
#include "../Core/MemGuard.hpp"

namespace GF {
	namespace IOModule {
		class Window;
		class GraphObject2D: public sf::Sprite,public Core::Object{
			friend Window;
		public:
			GraphObject2D() = default;
			void setVisible(bool enabled);
			bool getVisible();
			void setSharedTexture(SharedTexture&);
			void setPosition(Posf);
			void setPosition(float, float);
			void move(Posf);
			void move(float,float);
			void setBlendMode(BlendMode);
			const BlendMode getBlendMode();
			void setShader(const Shader&);

			virtual const SharedTexture& getTexture() = 0;
			virtual const Sizef getSize();
		protected:
			virtual void render(sf::RenderTarget* window);
			virtual bool checkClicked(Posf);
			virtual void mouseRelease(Events::MouseButtonArgs);
			virtual void mouseMove(Events::MouseMoveArgs);
		public:
			GF::Core::Events::Event<Events::EventArgs> Render;
			GF::Core::Events::Event<Events::MouseButtonArgs> MousePress;
			GF::Core::Events::Event<Events::MouseButtonArgs> MouseRelease;
			GF::Core::Events::Event<Events::MouseMoveArgs> MouseMove;

			GF::Core::Events::Event<Events::EventArgs> GainedFocus;
			GF::Core::Events::Event<Events::EventArgs> LostFocus;

			GF::Core::Events::Event<Events::KeyboardArgs> KeyPressed;
			GF::Core::Events::Event<Events::KeyboardArgs> KeyRelease;
			GF::Core::Events::Event<Events::TextTypeArgs> TextType;
		public:
			unsigned caMask = 0xFFFFFF00;
			bool clickable = false;
			Rectf caArea;
		protected:
			sf::RenderStates rs=sf::RenderStates::Default;
			bool visible=false;
		};
	}
}