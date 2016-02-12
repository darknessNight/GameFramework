#pragma once
#include "GraphObject.h"
#include "Texture.h"
#include "../Core/Types.h"

namespace GF {
	namespace IOModule {
		class Image :public GraphObject2D {
		public:
			Image() = delete;
			Image(const Image&);
			Image(Size size);
			void appendCamera(const Camera &cam);
			void importFromTexture(Core::MemGuard<Texture2D>);
			Core::MemGuard<Texture2D> exportTexture();
			bool loadFromMemory(const void * mem, unsigned size);
			bool loadFromStream(std::istream & stream);
			bool loadFromFile(std::string path);
			void SaveToFile(std::string path);
			void draw(Drawable& some, BlendMode bm = BlendNone, Shader* shader = nullptr, SharedTexture* texture=nullptr);
			void clear(Color color = Color::Black);
			void setSmooth(bool enable);
			void setRepeat(bool enable);
			bool getRepeat();
			bool getSmooth();
			const Sizef getSize();
			const SharedTexture& getTexture()override;
			void setSharedTexture(SharedTexture&)=delete;
		private:
			void lock();
			void unlock();
			void render(sf::RenderTarget* window) override;
		private:
			std::mutex mutex;
			bool edited = false;
			sf::RenderTexture texture;
		};
	}
}