#include "animation.hpp"

Animation::Animation( sf::Texture* texture )
	:	m_texture( texture )
{
}

Animation::~Animation()
{
}

void Animation::setTexture( sf::Texture* texture )
{
	m_texture = texture;
}

sf::Texture* Animation::getTexture() const
{
	return m_texture;
}

size_t Animation::size() const
{
	return m_frames.size();
}

const sf::IntRect& Animation::getRect( size_t index ) const
{
	return m_frames[ index ];
}

Animation& Animation::addFrame( const sf::IntRect& rect )
{
	m_frames.emplace_back( rect );
	return *this;
}

Animation& Animation::addFramesHorizon( int x, int y, int horizon )
{
	const sf::Vector2u size = m_texture->getSize();
	const float delta_x = size.x / float( x );
	const float delta_y = size.y / float( y );

	for ( size_t cntr = 0; cntr < x; cntr++ )
		addFrame( sf::IntRect( cntr * delta_x, horizon * delta_y, delta_x, delta_y ) );
	return *this;
}

Animation& Animation::addFramesPillar( int x, int y, int pillar )
{
	const sf::Vector2u size = m_texture->getSize();
	const float delta_x = size.x / float( x );
	const float delta_y = size.y / float( y );

	for ( size_t cntr = 0; cntr < y; cntr++ )
		addFrame( sf::IntRect( pillar * delta_x, cntr * delta_y, delta_x, delta_y ) );
	return *this;
}
