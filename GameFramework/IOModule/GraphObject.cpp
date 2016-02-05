#include "GraphObject.h"

namespace GF {
	namespace IOModule {
		void GraphObject2D::setVisible(bool enabled)
		{
			visible = enabled;
		}

		void GraphObject2D::setPos(const Posf p)
		{
			sprite.setPosition(p);
		}

		void GraphObject2D::setColor(const Color c)
		{
			sprite.setColor(c);
		}

		void GraphObject2D::setTransformPoint(Posf p)
		{
			sprite.setOrigin(p);
		}

		void GraphObject2D::setRotation(float angle)
		{
			sprite.setRotation(angle);
		}

		void GraphObject2D::setScale(float xScale, float yScale)
		{
			sprite.setScale(xScale, yScale);
		}

		void GraphObject2D::setScale(Sizef scale)
		{
			sprite.setScale(scale);
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
		const Color & GraphObject2D::getColor()
		{
			return sprite.getColor();
		}
		const Posf & GraphObject2D::getTransformPoint()
		{
			return sprite.getOrigin();
		}
		const float & GraphObject2D::getRotation()
		{
			return sprite.getRotation();
		}
		const Sizef & GraphObject2D::getScale()
		{
			return sprite.getScale();
		}
		void GraphObject2D::rotate(float angle)
		{
			sprite.rotate(angle);
		}
		void GraphObject2D::scale(float x, float y)
		{
			sprite.scale(x, y);
		}
		void GraphObject2D::scale(Sizef scale)
		{
			sprite.scale(scale);
		}
	}
}