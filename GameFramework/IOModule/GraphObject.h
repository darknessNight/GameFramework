#pragma once
#include <SFML\Graphics.hpp>
#include "Interfaces.h"

namespace GF {
	namespace IOModule {
		class Window;
		class GraphObject2D: public sf::Sprite{
			friend Window;
		public:
			GraphObject2D() = default;
			virtual void setVisible(bool enabled);
			virtual bool getVisible();
			void setSharedTexture(SharedTexture&);
			void setPosition(Posf);
			virtual const SharedTexture& getTexture() = 0;
			virtual const Sizef& getSize();
		protected:
			virtual void render(sf::RenderTarget* window);
			virtual bool checkClicked(Posf);
			virtual void mouseRelease(Events::MouseButtArgs);
		public:
			GF::Core::Events::Event<Events::EventArgs> Render;
			GF::Core::Events::Event<Events::MouseButtArgs> MousePress;
			GF::Core::Events::Event<Events::MouseButtArgs> MouseRelease;
		public:
			unsigned caMask = 0xFFFFFF00;
			bool clickable = false;
			Rectf caArea;
		protected:
			bool visible=false;
		};
	}
}