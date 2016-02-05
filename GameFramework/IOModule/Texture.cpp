#include "Texture.h"

GF::IOModule::Texture2D::Texture2D(Size size)
{
	texture.create(size.x, size.y);
	sprite.setTexture(texture);
}

void GF::IOModule::Texture2D::LoadFromFile(std::string path)
{
	texture.loadFromFile(path);
}

void GF::IOModule::Texture2D::setSmooth(bool enabled)
{
	texture.setSmooth(enabled);
}

void GF::IOModule::Texture2D::render(sf::RenderWindow* window)
{
	if(visible)
		window->draw(sprite);
}