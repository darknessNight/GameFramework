#pragma once
#include"GraphObject.h"
#include "Texture.h"
#include "../Core/Types.h"

namespace GF {
	namespace IOModule {
		class MultipleGraph2D:public GraphObject2D{
		public:
			MultipleGraph2D() = delete;
			MultipleGraph2D(Size);
			~MultipleGraph2D();
			void append(Core::MemGuard<GraphObject2D>);
			void remove(unsigned index);
			void remove(Core::MemGuard<GraphObject2D>);
			void clear();
			void setActive(int i);
			unsigned size();
			const sf::Texture& getTexture();
		private:
			std::vector<Core::MemGuard<GraphObject2D>> objects;
			sf::Texture empty;
			int active = -1;
			Size stdSize;
		};
	}
}