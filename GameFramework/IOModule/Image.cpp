#include "Image.h"

namespace GF {
	namespace IOModule {
		Image::Image(Size size)
		{
			if (!texture.create(size.x, size.y))
				throw std::exception("Cannot create RenderTexture");
		}

		void Image::render(sf::RenderTarget * window)
		{
		}
		
	}
}