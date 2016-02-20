#include "MultipleGraph.h"
namespace GF {
	namespace IOModule {
		MultipleGraph2D::MultipleGraph2D(Size s)
		{
			empty.create(s.x, s.y);
			stdSize = s;
		}

		MultipleGraph2D::~MultipleGraph2D()
		{
			
			objects.clear();
		}

		void MultipleGraph2D::append(Core::MemGuard<GraphObject2D> el)
		{
			objects.push_back(el);
		}

		void MultipleGraph2D::remove(unsigned index)
		{
			
			if (index < objects.size()) {
				auto i = objects.begin();
				i += index;
				std::swap(i,objects.end());objects.pop_back();
			}
			if (active >= objects.size()) setActive(-1);
		}

		void MultipleGraph2D::remove(Core::MemGuard<GraphObject2D> el)
		{
			
			for (auto i = objects.begin(); i != objects.end();i++) {
				if ((*i) == el) {
					std::swap(i,objects.end());objects.pop_back();
					break;
				}
			}
			if (active >= objects.size()) setActive(-1);
		}

		void MultipleGraph2D::clear()
		{
			
			objects.clear();
		}

		void MultipleGraph2D::setActive(int i)
		{
			
			active = i;
			if (i < objects.size() && i >= 0) {
				sf::Sprite::setTexture((objects[i])->getTexture());
			}
			else {
				sf::Sprite::setTexture(empty);
				active = -1;
			}
		}

		unsigned MultipleGraph2D::size()
		{
			
			return objects.size();
		}

		const SharedTexture & MultipleGraph2D::getTexture()
		{
			
			if (active >= 0)
			return ((GraphObject2D*)&*objects[active])->getTexture();
			else return empty;
		}
	}
}