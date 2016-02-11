#pragma once
#include "GraphObject.h"
namespace GF {
	namespace IOModule {
		class Image;
		class Texture2D :public GraphObject2D{
			friend Image;
		public:
			Texture2D() = delete;
			Texture2D(const SharedTexture& tex);
			Texture2D(Size size);
			void loadFromFile(std::string path);
			void loadFromMemory(const void* mem, unsigned size);
			void loadFromStream(std::istream& stream);
			void setSmooth(bool enabled);
			void setRepeat(bool enabled);
			bool getSmooth();
			bool getRepeat();

			const SharedTexture& getTexture() override;
			void setSharedTexture(SharedTexture&)=delete;
		private:
			sf::Texture texture;
		};
	}
}