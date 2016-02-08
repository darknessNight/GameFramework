#pragma once
#include <SFML\Graphics.hpp>
namespace GF {
	namespace IOModule {
		//TODO zast¹piæ typedef typami lub interfejsami
		typedef sf::Mouse Mouse;
		typedef sf::Keyboard Keyboard;
		typedef sf::Joystick Joystick;
		typedef sf::NonCopyable NonCopyable;
		typedef sf::Vector2i Pos;
		typedef sf::Vector2f Posf;
		typedef sf::Vector2u Size;
		typedef sf::Vector2f Sizef;
		typedef sf::Color Color;
		typedef sf::Font Font;
		typedef sf::Shader Shader;
		typedef sf::BlendMode BlenMode;
		typedef sf::Text Text;
		typedef sf::Drawable Drawable;
		typedef sf::IntRect Rect;
		typedef sf::FloatRect Rectf;
		typedef sf::View Camera;
		typedef sf::Time Time;
		namespace Shapes {
			typedef sf::CircleShape Circle;
			typedef sf::RectangleShape Rectangle;
			typedef sf::ConvexShape ConvexShape;
		}
	}
}