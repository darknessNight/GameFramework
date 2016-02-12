#include "Image.h"

namespace GF {
	namespace IOModule {
		Image::Image(const Image &ref)
		{
			lock();
			sf::Sprite sprite;
			sprite.setTexture(ref.texture.getTexture());
			texture.draw(sprite);
			texture.display();
			edited = true;
			unlock();
		}

		Image::Image(Size size)
		{
			lock();
			if (!texture.create(size.x, size.y))
				throw std::runtime_error("Cannot create RenderTexture");
			caArea.height = size.y; caArea.width = size.x;
			edited = true;
			unlock();
		}

		void Image::appendCamera(const Camera& cam)
		{
			lock();
			texture.setView(cam);
			edited = true;
			unlock();
		}

		void Image::importFromTexture(Core::MemGuard<Texture2D> tex)
		{
			lock();
			Core::MemGuard<Texture2D> tmp = tex;
			sf::Sprite sprite;
			sprite.setTexture(tmp->texture);
			texture.draw(sprite);
			edited = true;
			unlock();
		}

		Core::MemGuard<Texture2D> Image::exportTexture()
		{
			lock();
			texture.display();
			Core::MemGuard<Texture2D> ret;
			ret = new Texture2D(texture.getTexture());
			unlock();
			return ret;
		}

		bool Image::loadFromMemory(const void * mem, unsigned size)
		{
			sf::Sprite sprite;
			sf::Texture tex;
			if (tex.loadFromMemory(mem, size)) {
				lock();
				sprite.setTexture(tex);
				texture.draw(sprite);
				edited = true;
				unlock();
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
				long long size = stream.tellg();
				stream.seekg(0, stream.beg);

				char *buff = new char[size + 1];
				stream.read(buff, size);

				if (!stream || !tex.loadFromMemory(buff, size)) {
					delete[] buff;
					return false;
				}
				delete[] buff;
				lock();
				sprite.setTexture(tex);
				texture.draw(sprite);
				edited = true;
				unlock();
				return true;
			}
			return false;
		}

		bool Image::loadFromFile(std::string path)
		{
			sf::Sprite sprite;
			sf::Texture tex;
			if (tex.loadFromFile(path)) {
				lock();
				sprite.setTexture(tex);
				texture.draw(sprite);
				edited = true;
				unlock();
				return true;
			}
			return false;
		}

		void Image::draw(Drawable & some, BlendMode bm, Shader* shader, SharedTexture* texture)
		{
			lock();
			sf::RenderStates rs=sf::RenderStates::Default;
			rs.blendMode = bm;
			rs.shader = shader;
			rs.texture = texture;
			this->texture.draw(some,rs);
			edited = true;
			unlock();
		}

		void Image::clear(Color color)
		{
			lock();
			texture.clear(color);
			edited = true;
			unlock();
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
			lock();
			texture.display();
			sf::Image im(texture.getTexture().copyToImage());
			unlock();
			if (!im.saveToFile(path))
				throw std::runtime_error("Cannot save to file");
		}

		const Sizef Image::getSize()
		{
			Sizef size;
			size.x = texture.getSize().x;
			size.y = texture.getSize().y;
			return size;
		}

		const sf::Texture & Image::getTexture()
		{
			std::lock_guard<std::mutex> lg(mutex);
			return texture.getTexture();
		}

		void Image::lock()
		{
			mutex.lock();
			texture.setActive();
		}

		void Image::unlock()
		{
			texture.setActive(false);
			mutex.unlock();
		}

		void Image::render(sf::RenderTarget * window)
		{
			if (visible) {
				lock();
				if (edited) {
					texture.display();
					sf::Sprite::setTexture(texture.getTexture());
					edited = false;
				}
				window->draw(*this, rs);
				unlock();
			}
		}

		void Image::setRepeat(bool enabled)
		{
			lock();
			texture.setRepeated(enabled);
			edited = true;
			unlock();
		}

		bool Image::getRepeat()
		{
			return texture.isRepeated();
		}
	}
}

