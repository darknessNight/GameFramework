#pragma once
#include <SFML\Graphics.hpp>
#include "Interfaces.h"

namespace GF {
	namespace IOModule {
		class Window;
		class GraphObject2D{
			friend Window;
		public:
			GraphObject2D() = default;
			GraphObject2D(const GraphObject2D& ref);
			void operator=(const GraphObject2D& ref);
			virtual bool operator==(const GraphObject2D& ref);
			virtual void setVisible(bool enabled);
			virtual void setPosition(const Posf p);
			virtual void setColor(const Color c);//change color of object (create color mask)
			virtual void setOrigin(Posf p);
			virtual void setRotation(float angle);//overrive current rotate
			virtual void setScale(float xScale, float yScale);// current scale
			virtual void setScale(Sizef scale);// current scale
			virtual bool getVisible();
			virtual const Posf& getPosition();
			virtual const Sizef& getSize();
			virtual const Color& getColor();
			virtual const Posf& getOrigin();
			virtual const float& getRotation();
			virtual const Sizef& getScale();
			virtual void rotate(float angle);//add to current rotate angle
			virtual void scale(float x, float y);//multiple current scale
			virtual void scale(Sizef scale);//multiple current scale;
			virtual void loadFromFile(std::string path) = 0;
			virtual void loadFromMemory(const void* mem, unsigned size) = 0;
			virtual void loadFromStream(std::istream& stream) = 0;
			//--
			virtual const sf::Texture& getTexture() = 0;
		protected:
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