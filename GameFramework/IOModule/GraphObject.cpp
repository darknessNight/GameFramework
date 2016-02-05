#include "GraphObject.h"

namespace GF {
	namespace IOModule {
		void GraphObject2D::setVisible(bool enabled)
		{
			visible = enabled;
			sprite.setColor(sf::Color::Green);
			sprite.setScale({ 2,2 });
		}

		void GraphObject2D::setPos(const Posf p)
		{
			sprite.setPosition(p);
		}

		bool GraphObject2D::getVisible()
		{
			return visible;
		}
		
		const Posf& GraphObject2D::getPos()
		{
			return sprite.getPosition();
		}
		
		const Sizef& GraphObject2D::getSize()
		{
			return sprite.getPosition();
		}
	}
}