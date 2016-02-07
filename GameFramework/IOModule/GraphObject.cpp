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

		bool GraphObject2D::operator==(const GraphObject2D & ref)
		{
			//std::lock_guard<std::mutex> guard(mutex);
			return ref.visible == visible && Render==ref.Render;
		}

		void GraphObject2D::setVisible(bool enabled)
		{
			//std::lock_guard<std::mutex> guard(mutex);
			visible = enabled;
		}

		void GraphObject2D::setPosition(const Posf p)
		{
			//std::lock_guard<std::mutex> guard(mutex);
			sprite.setPosition(p);
		}

		void GraphObject2D::setColor(const Color c)
		{
			//std::lock_guard<std::mutex> guard(mutex);
			sprite.setColor(c);
		}

		void GraphObject2D::setOrigin(Posf p)
		{
			//std::lock_guard<std::mutex> guard(mutex);
			sprite.setOrigin(p);
		}

		void GraphObject2D::setRotation(float angle)
		{
			//std::lock_guard<std::mutex> guard(mutex);
			sprite.setRotation(angle);
		}

		void GraphObject2D::setScale(float xScale, float yScale)
		{
			//std::lock_guard<std::mutex> guard(mutex);
			sprite.setScale(xScale, yScale);
		}

		void GraphObject2D::setScale(Sizef scale)
		{
			//std::lock_guard<std::mutex> guard(mutex);
			sprite.setScale(scale);
		}

		bool GraphObject2D::getVisible()
		{
			//std::lock_guard<std::mutex> guard(mutex);
			return visible;
		}
		
		const Posf& GraphObject2D::getPosition()
		{
			//std::lock_guard<std::mutex> guard(mutex);
			return sprite.getPosition();
		}
		
		const Sizef& GraphObject2D::getSize()
		{
			//std::lock_guard<std::mutex> guard(mutex);
			if(sprite.getTexture()!=nullptr)
				return{ static_cast<float>(sprite.getTexture()->getSize().x),static_cast<float>(sprite.getTexture()->getSize().y) };
			else return{ 0,0 };
		}
		const Color & GraphObject2D::getColor()
		{
			//std::lock_guard<std::mutex> guard(mutex);
			return sprite.getColor();
		}
		const Posf & GraphObject2D::getOrigin()
		{
			//std::lock_guard<std::mutex> guard(mutex);
			return sprite.getOrigin();
		}
		const float & GraphObject2D::getRotation()
		{
			//std::lock_guard<std::mutex> guard(mutex);
			return sprite.getRotation();
		}
		const Sizef & GraphObject2D::getScale()
		{
			//std::lock_guard<std::mutex> guard(mutex);
			return sprite.getScale();
		}
		void GraphObject2D::rotate(float angle)
		{
			//std::lock_guard<std::mutex> guard(mutex);
			sprite.rotate(angle);
		}
		void GraphObject2D::scale(float x, float y)
		{
			//std::lock_guard<std::mutex> guard(mutex);
			sprite.scale(x, y);
		}
		void GraphObject2D::scale(Sizef scale)
		{
			//std::lock_guard<std::mutex> guard(mutex);
			sprite.scale(scale);
		}
	}
}