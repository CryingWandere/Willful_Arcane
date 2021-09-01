#pragma once

#include < sstream >

#include < SFML/Window/Keyboard.hpp >
#include < SFML/System/Vector2.hpp >

//Forward declaration
namespace sf
{
	class Sprite;
	class Text;
}
//

std::string toString( sf::Keyboard::Key key );

float toDegree( float radian );
float toRadian( float degree );

float length( sf::Vector2f vect );
sf::Vector2f unitVector( sf::Vector2f vect );

int getRandomInt( int exMin, int exMax );
int getRandomInt( int exMax );

void centerOrigin( sf::Sprite& sprite );
void centerOrigin( sf::Text& text );