#pragma once
#include "GraphObject.h"
#include "Texture.h"

namespace GF {
	namespace IOModule {
		class Image :public GraphObject2D{
		public:
			Image() = delete;
			Image(Size size);
			void importFromTexture(Texture2D& texture);
			const Texture2D exportTexture();
			void loadFromMemory(const void * mem, unsigned size) override;
			void loadFromStream(std::istream & stream) override;
			void loadFromFile(std::string path) override;
			void draw(Drawable& some);
			void clear(Color color = Color::Black);
			void SaveToFile(std::string path);
		private:
			void render(sf::RenderTarget* window) override;

		private:
			bool edited = false;
			sf::RenderTexture texture;
		};
	}
}