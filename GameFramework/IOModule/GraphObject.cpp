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

		const Sizef& GraphObject2D::getSize()
		{
			return{ static_cast<float>(getTextureRect().width), static_cast<float>(getTextureRect().width) };
		}

		void GraphObject2D::render(sf::RenderTarget * window)
		{
			if (visible) {
				Events::EventArgs args;
				this->Render(this,args);
				window->draw(*this);
			}
		}
		bool GraphObject2D::checkClicked(Posf pos)
		{
			float xe = caArea.left + caArea.width;
			float ye = caArea.top + caArea.height;
			if (pos.x >= caArea.left && pos.x <= xe &&
				pos.y >= caArea.top && pos.y <= ye) {
				Events::MouseButtArgs args;
				args.x = pos.x - caArea.left;
				args.y = pos.y - caArea.top;

				if (getTexture().copyToImage().getPixel(args.x,args.y).toInteger()&caMask != 0) {
					MousePress(this, args);
					return true;
				}
			}
			return false;
		}
	}
}