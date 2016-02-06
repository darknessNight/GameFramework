#pragma once
#include "GraphObject.h"

namespace GF {
	namespace IOModule {
		class Image;
		class Texture2D :public GraphObject2D, public ITexture2D{
			friend Image;
		public:
			Texture2D() = delete;
			Texture2D(const sf::Texture& tex);
			Texture2D(Size size);
			void loadFromFile(std::string path) override;
			void loadFromMemory(const void* mem, unsigned size);
			void loadFromStream(std::istream& stream);
			void setSmooth(bool enabled);
		private:
			void render(sf::RenderTarget* window) override;
		private:
			sf::Texture texture;
		};
	}
}