#pragma once
#include "GraphObject.h"

namespace GF {
	namespace IOModule {
		class Image :public GraphObject2D, public IImage {
		public:
			Image() = delete;
			Image(Size size);
			void importFromTexture();
		private:
			void render(sf::RenderTarget* window) override;

		private:
			sf::RenderTexture texture;
		};
	}
}