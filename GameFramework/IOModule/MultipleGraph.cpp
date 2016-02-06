#include "MultipleGraph.h"

namespace GF {
	namespace IOModule {
		MultipleGraph2D::MultipleGraph2D(Size s)
		{
			empty.create(s.x, s.y);
			stdSize = s;
		}

		void MultipleGraph2D::append(std::shared_ptr<GraphObject2D> el)
		{
			if (el->getSize().x != stdSize.x || el->getSize().y != stdSize.y) {
				throw std::exception("Target size is incompatibile");
			}
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

		void MultipleGraph2D::setActive(int i)
		{
			active = i;
			if (i < objects.size() && i >= 0) {
				sprite.setTexture(objects[i]->getTexture());
			}
			else {
				sprite.setTexture(empty);
				active = -1;
			}
		}

		unsigned MultipleGraph2D::size()
		{
			return objects.size();
		}

		void MultipleGraph2D::loadFromMemory(const void * mem, unsigned size)
		{
			if (active >= 0)
				objects[active]->loadFromMemory(mem, size);
		}

		void MultipleGraph2D::loadFromStream(std::istream & stream)
		{
			if (active >= 0)
				objects[active]->loadFromStream(stream);
		}

		void MultipleGraph2D::loadFromFile(std::string path)
		{
			if (active >= 0)
				objects[active]->loadFromFile(path);
		}

		const sf::Texture & MultipleGraph2D::getTexture()
		{
			if (active >= 0)
			return objects[active]->getTexture();
			else return empty;
		}

		void MultipleGraph2D::render(sf::RenderTarget * window)
		{
			window->draw(sprite);
		}
	}
}