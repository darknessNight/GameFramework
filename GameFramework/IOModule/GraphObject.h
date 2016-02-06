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
			void setColor(const Color c);//change color of object (create color mask)
			void setOrigin(Posf p);
			void setRotation(float angle);//overrive current rotate
			void setScale(float xScale, float yScale);//override current scale
			void setScale(Sizef scale);//override current scale
			bool getVisible();
			const Posf& getPos();
			const Sizef& getSize();
			const Color& getColor();
			const Posf& getTransformPoint();
			const float& getRotation();
			const Sizef& getScale();
			void rotate(float angle);//add to current rotate angle
			void scale(float x, float y);//multiple current scale
			void scale(Sizef scale);//multiple current scale
			virtual void loadFromFile(std::string path) = 0;
		protected:
			virtual void render(sf::RenderTarget* window) = 0;
		public:
			Events::Event<Events::EventArgs> Render;
		protected:
			sf::Sprite sprite;
			bool changed = false;
			bool visible=false;
		};
	}
}