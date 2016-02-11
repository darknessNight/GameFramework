#include "Image.h"

namespace GF {
	namespace IOModule {
		Image::Image(const Image &ref)
		{
			sf::Sprite sprite;
			sprite.setTexture(ref.texture.getTexture());
			texture.draw(sprite);
			texture.display();
			edited = true;
		}

		Image::Image(Size size)
		{
			if (!texture.create(size.x, size.y))
				throw std::exception("Cannot create RenderTexture");
			caArea.height = size.y; caArea.width = size.x;
			edited = true;
		}

		void Image::appendCamera(const Camera& cam)
		{
			texture.setView(cam);
			edited = true;
		}

		void Image::importFromTexture(Core::MemGuard<Texture2D> tex)
		{
			Core::MemGuard<Texture2D> tmp = tex;
			sf::Sprite sprite;
			sprite.setTexture(tmp->texture);
			texture.draw(sprite);
			edited = true;
		}

		Core::MemGuard<Texture2D> Image::exportTexture()
		{
			texture.display();
			edited = false;
			Core::MemGuard<Texture2D> ret;
			ret = new Texture2D(texture.getTexture());
			return ret;
		}

		bool Image::loadFromMemory(const void * mem, unsigned size)
		{
			sf::Sprite sprite;
			sf::Texture tex;
			if (tex.loadFromMemory(mem, size)) {
				sprite.setTexture(tex);
				texture.draw(sprite);
				edited = true;
				return true;
			}
			return false;
		}

		bool Image::loadFromStream(std::istream & stream)
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
					return false;
				}
				delete[] buff;

				sprite.setTexture(tex);
				texture.draw(sprite);
				edited = true;
				return true;
			}
		}

		bool Image::loadFromFile(std::string path)
		{
			sf::Sprite sprite;
			sf::Texture tex;
			if (tex.loadFromFile(path)) {
				sprite.setTexture(tex);
				texture.draw(sprite);
				edited = true;
				return true;
			}
			return false;
		}

		void Image::draw(Drawable & some)
		{
			texture.draw(some);
			edited = true;
		}

		void Image::clear(Color color)
		{
			texture.clear(color);
			edited = true;
		}

		void Image::setSmooth(bool enable)
		{
			texture.setSmooth(enable);
			edited = true;
		}

		bool Image::getSmooth()
		{
			return texture.isSmooth();
		}

		void Image::SaveToFile(std::string path)
		{
			texture.display();
			sf::Image im(texture.getTexture().copyToImage());
			if (!im.saveToFile(path))
				throw std::exception("Cannot save to file");
		}

		const Sizef & Image::getSize()
		{
			Sizef size;
			size.x = texture.getSize().x;
			size.y = texture.getSize().y;
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
					sf::Sprite::setTexture(texture.getTexture());
					edited = false;
				}
				window->draw(*this, rs);
			}
		}

		void Image::setRepeat(bool enabled)
		{
			texture.setRepeated(enabled);
			edited = true;
		}

		bool Image::getRepeat()
		{
			return texture.isRepeated();
		}
	}
}

