#pragma once
#include "GraphObject.h"

namespace GF {
	namespace IOModule {
		class Texture2D :public GraphObject2D, public ITexture2D{
			friend IImage2D;
		public:
			Texture2D() = delete;
			Texture2D(Size size);
			void LoadFromFile(std::string path) override;
			void setSmooth(bool enabled);
			using GraphObject2D::getPos;
		private:
			void render(sf::RenderWindow* window) override;
		private:
			sf::Texture texture;
		};
	}
}