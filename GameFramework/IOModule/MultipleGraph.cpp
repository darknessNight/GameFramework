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
			std::lock_guard<std::mutex> lock(mutex);
			objects.clear();
		}

		void MultipleGraph2D::append(std::shared_ptr<GraphObject2D> el)
		{
			std::lock_guard<std::mutex> lock(mutex);
			if (el->getSize().x != stdSize.x || el->getSize().y != stdSize.y) {
				throw std::exception("Target size is incompatibile");
			}
			objects.push_back(el);
		}

		void MultipleGraph2D::remove(unsigned index)
		{
			std::lock_guard<std::mutex> lock(mutex);
			if (index < objects.size()) {
				auto i = objects.begin();
				i += index;
				i = objects.erase(i);
			}
			if (active >= objects.size()) setActive(-1);
		}

		void MultipleGraph2D::clear()
		{
			std::lock_guard<std::mutex> lock(mutex);
			objects.clear();
		}

		void MultipleGraph2D::setActive(int i)
		{
			std::lock_guard<std::mutex> lock(mutex);
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
			std::lock_guard<std::mutex> lock(mutex);
			return objects.size();
		}

		void MultipleGraph2D::loadFromMemory(const void * mem, unsigned size)
		{
			std::lock_guard<std::mutex> lock(mutex);
			if (active >= 0)
				objects[active]->loadFromMemory(mem, size);
		}

		void MultipleGraph2D::loadFromStream(std::istream & stream)
		{
			std::lock_guard<std::mutex> lock(mutex);
			if (active >= 0)
				objects[active]->loadFromStream(stream);
		}

		void MultipleGraph2D::loadFromFile(std::string path)
		{
			std::lock_guard<std::mutex> lock(mutex);
			if (active >= 0)
				objects[active]->loadFromFile(path);
		}

		const sf::Texture & MultipleGraph2D::getTexture()
		{
			std::lock_guard<std::mutex> lock(mutex);
			if (active >= 0)
			return objects[active]->getTexture();
			else return empty;
		}

		void MultipleGraph2D::render(sf::RenderTarget * window)
		{
			std::lock_guard<std::mutex> lock(mutex);
			if(active>=0)
				window->draw(sprite);
		}
	}
}