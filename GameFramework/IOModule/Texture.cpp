#include "Texture.h"
#include <fstream>

GF::IOModule::Texture2D::Texture2D(const sf::Texture & tex):texture(tex)
{
}

GF::IOModule::Texture2D::Texture2D(Size size)
{
	if(!texture.create(size.x, size.y))
		throw std::exception("Cannot create Texture");
	sprite.setTexture(texture);
}

void GF::IOModule::Texture2D::loadFromFile(std::string path)
{
	if(!texture.loadFromFile(path))
		throw std::exception("Cannot load from file");
}

void GF::IOModule::Texture2D::loadFromMemory(const void* mem, unsigned size)
{
	if (!texture.loadFromMemory(mem, size))
		throw std::exception("Cannot load from memory");
}

void GF::IOModule::Texture2D::loadFromStream(std::istream& stream)
{
	if (stream.good()) {
		stream.seekg(0, stream.end);
		unsigned size = stream.tellg();
		stream.seekg(0, stream.beg);

		char *buff=new char[size+1];
		stream.read(buff, size);

		if (!stream || !texture.loadFromMemory(buff, size)) {
			delete[] buff;
			throw std::exception("Cannot load from stream");
		}

		delete[] buff;
	}
}

void GF::IOModule::Texture2D::setSmooth(bool enabled)
{
	texture.setSmooth(enabled);
}

const sf::Texture & GF::IOModule::Texture2D::getTexture()
{
	return texture;
}

void GF::IOModule::Texture2D::render(sf::RenderTarget* window)
{
	if(visible)
		window->draw(sprite);
}