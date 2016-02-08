#pragma once
#include "GraphObject.h"
namespace GF {
	namespace IOModule {
		class Image;
		class Texture2D :public GraphObject2D{
			friend Image;
		public:
			Texture2D() = delete;
			Texture2D(const sf::Texture& tex);
			Texture2D(Size size);
			void loadFromFile(std::string path) override;
			void loadFromMemory(const void* mem, unsigned size) override;
			void loadFromStream(std::istream& stream) override;
			void setSmooth(bool enabled);
			void setRepeat(bool enabled);
			bool getSmooth();
			bool getRepeat();

			const sf::Texture& getTexture()override;
		private:
			void render(sf::RenderTarget* window) override;
		private:
			sf::Texture texture;
		};
	}
}