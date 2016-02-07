#include "Image.h"

namespace GF {
	namespace IOModule {
		Image::Image(const Image &)
		{
		}

		Image::Image(Size size)
		{
			if (!texture.create(size.x, size.y))
				throw std::exception("Cannot create RenderTexture");
		}

		void Image::setCamera(const Camera& cam)
		{
			texture.setView(cam);
		}

		void Image::importFromTexture(std::shared_ptr<Texture2D> tex)
		{
			std::lock_guard<std::mutex> guard(mutex);
			sf::Sprite sprite;
			sprite.setTexture(tex->texture);
			texture.draw(sprite);
			texture.display();
		}

		std::shared_ptr<Texture2D> Image::exportTexture()
		{
			std::lock_guard<std::mutex> guard(mutex);
			texture.display();
			return std::make_shared<Texture2D>(texture.getTexture());
		}

		void Image::loadFromMemory(const void * mem, unsigned size)
		{
			sf::Sprite sprite;
			sf::Texture tex;
			if (!tex.loadFromMemory(mem, size))
				throw std::exception("Cannot load from memory");
			sprite.setTexture(tex);
			std::lock_guard<std::mutex> guard(mutex);
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
				std::lock_guard<std::mutex> guard(mutex);
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
			std::lock_guard<std::mutex> guard(mutex);
			texture.draw(sprite);
			edited = true;
		}

		void Image::draw(Drawable & some)
		{
			std::lock_guard<std::mutex> guard(mutex);
			texture.draw(some);
			edited = true;
		}

		void Image::clear(Color color)
		{
			std::lock_guard<std::mutex> guard(mutex);
			texture.clear(color);
			edited = true;
		}

		void Image::setSmooth(bool enable)
		{
			std::lock_guard<std::mutex> guard(mutex);
			texture.setSmooth(enable);
		}

		bool Image::getSmooth()
		{
			std::lock_guard<std::mutex> guard(mutex);
			return texture.isSmooth();
		}

		void Image::SaveToFile(std::string path)
		{
			std::lock_guard<std::mutex> guard(mutex);
			texture.display();
			sf::Image im(texture.getTexture().copyToImage());
			if(!im.saveToFile(path))
				throw std::exception("Cannot save to file");
		}

		const Sizef & Image::getSize()
		{
			std::lock_guard<std::mutex> guard(mutex);
			Sizef size;
			size.x= texture.getSize().x;
			size.y= texture.getSize().y;
			return size;
		}

		const sf::Texture & Image::getTexture()
		{
			std::lock_guard<std::mutex> guard(mutex);
			return texture.getTexture();
		}

		void Image::render(sf::RenderTarget * window)
		{
			if (visible) {
				std::lock_guard<std::mutex> guard(mutex);
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