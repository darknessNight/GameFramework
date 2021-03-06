#include "Texture.h"
#include <fstream>
using namespace GF::IOModule;
GF::IOModule::Texture2D::Texture2D(const SharedTexture & tex):texture(tex)
{
	sf::Sprite::setTexture(texture);
}

GF::IOModule::Texture2D::Texture2D(Size size)
{
	if(!texture.create(size.x, size.y))
		throw std::exception("Cannot create Texture");
	sf::Sprite::setTexture(texture);
	caArea.height = size.y; caArea.width = size.x;

}

bool GF::IOModule::Texture2D::loadFromFile(std::string path)
{
	return texture.loadFromFile(path);
}

bool GF::IOModule::Texture2D::loadFromMemory(const void* mem, unsigned size)
{
	return texture.loadFromMemory(mem, size);
}

bool GF::IOModule::Texture2D::loadFromStream(std::istream& stream)
{

	if (stream.good()) {
		stream.seekg(0, stream.end);
		long long size = stream.tellg();
		stream.seekg(0, stream.beg);

		char *buff=new char[size+1];
		stream.read(buff, size);

		if (!stream || !texture.loadFromMemory(buff, size)) {
			delete[] buff;
			return false;
		}

		delete[] buff;
		return true;
	}
	return false;
}

inline void GF::IOModule::Texture2D::setSmooth(bool enabled)
{
	texture.setSmooth(enabled);
}

inline void GF::IOModule::Texture2D::setRepeat(bool enabled)
{
	texture.setRepeated(enabled);
}

inline bool GF::IOModule::Texture2D::getSmooth()
{
	return texture.isSmooth();
}

inline bool GF::IOModule::Texture2D::getRepeat()
{
	return texture.isRepeated();
}

inline const sf::Texture & GF::IOModule::Texture2D::getTexture()
{
	return texture;
}