#pragma once

#include < SFML/Graphics/Sprite.hpp >
#include < SFML/Graphics/Texture.hpp >

#include < vector >

class Animation
{
public:
	Animation( sf::Texture* texture = nullptr );
	~Animation();

	void setTexture( sf::Texture* texture );
	sf::Texture* getTexture() const;

	Animation& addFrame( const sf::IntRect& rect );
	Animation& addFramesHorizon( int x, int y, int horizon );
	Animation& addFramesPillar( int x, int y, int pillar );

	size_t size() const;
	const sf::IntRect& getRect( size_t index ) const;

private:
	friend class AnimatedSprite;
	std::vector< sf::IntRect > m_frames;
	sf::Texture* m_texture;

};
