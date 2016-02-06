#include "Image.h"

namespace GF {
	namespace IOModule {
		Image::Image(Size size)
		{
			if (!texture.create(size.x, size.y))
				throw std::exception("Cannot create RenderTexture");
		}

		void Image::importFromTexture(Texture2D& tex)
		{
			sf::Sprite sprite;
			sprite.setTexture(tex.texture);
			texture.draw(sprite);
		}

		const Texture2D Image::exportTexture()
		{
			texture.display();
			return Texture2D(texture.getTexture());
		}

		void Image::loadFromMemory(const void * mem, unsigned size)
		{
			sf::Sprite sprite;
			sf::Texture tex;
			if (!tex.loadFromMemory(mem, size))
				throw std::exception("Cannot load from memory");
			sprite.setTexture(tex);
			texture.draw(sprite);
		}

		void Image::loadFromStream(std::istream & stream)
		{
			sf::Sprite sprite;
			sf::Texture tex;
			if (stream.good()) {
				stream.seekg(0, stream.end);
				unsigned size = stream.tellg();
				stream.seekg(0, stream.beg);

				char *buff = new char[size + 1];
				stream.read(buff, size);

				if (!stream || !tex.loadFromMemory(buff, size)) {
					delete[] buff;
					throw std::exception("Cannot load from stream");
				}
				delete[] buff;

				sprite.setTexture(tex);
				texture.draw(sprite);
			}
		}

		void Image::loadFromFile(std::string path)
		{
			sf::Sprite sprite;
			sf::Texture tex;
			if(!tex.loadFromFile(path))
				throw std::exception("Cannot load from file");
			sprite.setTexture(tex);
			texture.draw(sprite);
		}

		void Image::draw(Drawable & some)
		{
			texture.draw(some);
			edited = true;
		}

		void Image::clear(Color color)
		{
			texture.clear();
			edited = true;
		}

		void Image::SaveToFile(std::string path)
		{
			texture.display();
			sf::Image im(texture.getTexture().copyToImage());
			if(!im.saveToFile(path))
				throw std::exception("Cannot save to file");
		}

		const Sizef & Image::getSize()
		{
			Sizef size;
			size.x= texture.getSize().x;
			size.y= texture.getSize().y;
			return size;
		}

		const sf::Texture & Image::getTexture()
		{
			return texture.getTexture();
		}

		void Image::render(sf::RenderTarget * window)
		{
			if (visible) {
				if (edited) {
					texture.display();
					sprite.setTexture(texture.getTexture());
					edited = false;
				}
				window->draw(sprite);
			}
		}
		
	}
}