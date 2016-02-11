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
				i = objects.erase(i);
			}
			if (active >= objects.size()) setActive(-1);
		}

		void MultipleGraph2D::remove(Core::MemGuard<GraphObject2D> el)
		{
			
			for (auto i = objects.begin(); i != objects.end();i++) {
				if ((*i) == el) {
					i = objects.erase(i);
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
				setTexture(((GraphObject2D*)&*objects[i])->getTexture());
			}
			else {
				setTexture(empty);
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