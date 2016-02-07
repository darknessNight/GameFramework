#include "GraphObject.h"

namespace GF {
	namespace IOModule {
		GraphObject2D::GraphObject2D(const GraphObject2D & ref)
		{
			operator=(ref);
		}

		void GraphObject2D::operator=(const GraphObject2D & ref)
		{
			this->sprite = ref.sprite;
			this->visible = ref.visible;
			this->Render = ref.Render;
		}

		void GraphObject2D::setVisible(bool enabled)
		{
			visible = enabled;
		}

		void GraphObject2D::setPosition(const Posf p)
		{
			sprite.setPosition(p);
		}

		void GraphObject2D::setColor(const Color c)
		{
			sprite.setColor(c);
		}

		void GraphObject2D::setOrigin(Posf p)
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
		
		const Posf& GraphObject2D::getPosition()
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
		const Posf & GraphObject2D::getOrigin()
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