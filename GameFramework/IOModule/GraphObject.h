#pragma once
#include <SFML\Graphics.hpp>
#include "Interfaces.h"

namespace GF {
	namespace IOModule {
		class Window;
		class GraphObject2D :public IGraphObject2D {
			friend Window;
		public:
			void setVisible(bool enabled);
			void setPos(const Posf p);
			bool getVisible();
			const Posf& getPos();
			const Sizef& getSize();
			virtual void LoadFromFile(std::string path) = 0;
		protected:
			virtual void render(sf::RenderWindow* window) = 0;
		public:
			Events::Event<Events::EventArgs> Render;
		protected:
			sf::Sprite sprite;
			bool changed = false;
			bool visible=false;
		};
	}
}