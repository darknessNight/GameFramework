#pragma once
#include"GraphObject.h"
#include "Texture.h"

namespace GF {
	namespace IOModule {
		class MultipleGraph2D:public GraphObject2D {
		public:
			MultipleGraph2D() = delete;
			MultipleGraph2D(Size);
			~MultipleGraph2D();
			void append(std::shared_ptr<GraphObject2D>);
			void remove(unsigned index);
			void clear();
			void setActive(int i);
			unsigned size();
			void loadFromMemory(const void * mem, unsigned size) override;
			void loadFromStream(std::istream & stream) override;
			void loadFromFile(std::string path) override;
			const sf::Texture& getTexture();
		private:
			std::vector<std::shared_ptr<GraphObject2D>> objects;
			sf::Texture empty;
			int active = -1;
			Size stdSize;

			// Inherited via GraphObject2D
			
			virtual void render(sf::RenderTarget * window) override;
		};
	}
}
