#pragma once
#include <SFML\Graphics.hpp>
#include "Interfaces.h"

namespace GF {
	namespace IOModule {
		class Window;
		class MultipleGraph2D;
		class GraphObject2D :public IGraphObject2D {
			friend Window;
		public:
			GraphObject2D() = default;
			GraphObject2D(const GraphObject2D& ref);
			void operator=(const GraphObject2D& ref);
			bool operator==(const GraphObject2D& ref);
			void setVisible(bool enabled);
			void setPosition(const Posf p);
			void setColor(const Color c);//change color of object (create color mask)
			void setOrigin(Posf p);
			void setRotation(float angle);//overrive current rotate
			void setScale(float xScale, float yScale);//override current scale
			void setScale(Sizef scale);//override current scale
			bool getVisible();
			const Posf& getPosition();
			virtual const Sizef& getSize();
			const Color& getColor();
			const Posf& getOrigin();
			const float& getRotation();
			const Sizef& getScale();
			void rotate(float angle);//add to current rotate angle
			void scale(float x, float y);//multiple current scale
			void scale(Sizef scale);//multiple current scale
			virtual void loadFromFile(std::string path) = 0;
			//--
			virtual const sf::Texture& getTexture() = 0;
		private:
			virtual void render(sf::RenderTarget* window) = 0;
		public:
			GF::Core::Events::Event<Events::EventArgs> Render;
			//int Render;
		protected:
			sf::Sprite sprite;
			//std::mutex mutex;
			bool visible=false;
		};
	}
}