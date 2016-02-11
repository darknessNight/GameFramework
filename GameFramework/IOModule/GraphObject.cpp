#include "GraphObject.h"

namespace GF {
	namespace IOModule {

		void GraphObject2D::setVisible(bool enabled)
		{
			visible = enabled;
		}

		bool GraphObject2D::getVisible()
		{
			return visible;
		}

		void GraphObject2D::setSharedTexture(SharedTexture & texture)
		{
			setTexture(texture);
		}

		void GraphObject2D::setPosition(Posf pos)
		{
			sf::Sprite::setPosition(pos);
			caArea.top = pos.y;
			caArea.left = pos.x;
		}

		void GraphObject2D::setPosition(float x, float y)
		{
			sf::Sprite::setPosition(x,y);
			caArea.top = y;
			caArea.left = x;
		}

		void GraphObject2D::move(Posf pos)
		{
			sf::Sprite::move(pos);
			caArea.top += pos.y;
			caArea.left += pos.x;
		}

		void GraphObject2D::move(float x, float y)
		{
			sf::Sprite::move(x, y);
			caArea.top += y;
			caArea.left += x;
		}

		void GraphObject2D::setBlendMode(BlendMode bm)
		{
			rs.blendMode = bm;
		}

		const BlendMode GraphObject2D::getBlendMode()
		{
			return rs.blendMode;
		}

		void GraphObject2D::setShader(const Shader & shader)
		{
			rs.shader = &shader;
		}

		const Sizef& GraphObject2D::getSize()
		{
			return{ static_cast<float>(getTextureRect().width), static_cast<float>(getTextureRect().width) };
		}

		void GraphObject2D::render(sf::RenderTarget * window)
		{
			if (visible) {
				Events::EventArgs args;
				this->Render(this,args);
				window->draw(*this,rs);
			}
		}

		bool GraphObject2D::checkClicked(Posf pos)
		{
			if (!clickable || !visible) return false;
			float xe = caArea.left + caArea.width;
			float ye = caArea.top + caArea.height;
			if (pos.x >= caArea.left && pos.x <= xe &&
				pos.y >= caArea.top && pos.y <= ye) {
				unsigned c = getTexture().copyToImage().getPixel(pos.x - caArea.left, pos.y - caArea.top).toInteger();
				if (c&caMask != 0) {
					Events::MouseButtArgs args;
					args.x = pos.x;
					args.y = pos.y;
					MousePress(this, args);
					return true;
				}
			}
			return false;
		}

		void GraphObject2D::mouseRelease(Events::MouseButtArgs args)
		{
			MouseRelease(this, args);
		}

		void GraphObject2D::mouseMove(Events::MouseMoveArgs args)
		{
			MouseMove(this, args);
		}
	}
}