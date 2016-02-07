#pragma once
#include "GraphObject.h"
#include "Texture.h"

namespace GF {
	namespace IOModule {
		class Image :public GraphObject2D{
		public:
			Image() = delete;
			Image(const Image&);
			Image(Size size);
			void setCamera(const Camera &cam);
			void importFromTexture(Core::MemGuard<Texture2D>);
			Core::MemGuard<Texture2D> exportTexture();
			void loadFromMemory(const void * mem, unsigned size) override;
			void loadFromStream(std::istream & stream) override;
			void loadFromFile(std::string path) override;
			void SaveToFile(std::string path);
			void draw(Drawable& some);
			void clear(Color color = Color::Black);
			void setSmooth(bool enable);
			bool getSmooth();
			const Sizef& getSize()override;
			const sf::Texture& getTexture()override;
		private:
			void render(sf::RenderTarget* window) override;
		private:
			bool edited = false;
			sf::RenderTexture texture;
		};
	}
}