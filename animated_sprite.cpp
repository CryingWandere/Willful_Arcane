#include "animated_sprite.hpp"

#include < cassert >

AnimatedSprite::FunctionType AnimatedSprite::defaultFunction = []()->void {};

AnimatedSprite::AnimatedSprite( Animation* animation,
								Status status,
								const sf::Time& delta,
								bool loop,
								int repeat			   )
	:	onFinished( defaultFunction )
	,	m_delta( delta )
	,	m_loop( loop )
	,	m_repeat( repeat )
	,	m_status( status )
{
	setAnimation( animation );
}

void AnimatedSprite::setAnimation( Animation* animation )
{
	if ( m_animation != animation )
	{
		m_animation = animation;
		m_elapsed = sf::Time::Zero;
		m_currentFrame = 0;
		setFrame( 0, true );
	}
}

Animation* AnimatedSprite::getAnimation() const
{
	return m_animation;
}

void AnimatedSprite::setFrameTime( sf::Time delta )
{
	m_delta = delta;
}

sf::Time AnimatedSprite::getFrameTime() const
{
	return m_delta;
}

void AnimatedSprite::setLoop( bool loop )
{
	m_loop = loop;
}

bool AnimatedSprite::getLoop() const
{
	return m_loop;
}

void AnimatedSprite::setRepeat( int rptnmb )
{
	m_repeat = rptnmb;
}

int AnimatedSprite::getRepeat() const
{
	return m_repeat;
}

//

void AnimatedSprite::play()
{
	m_status = Playing;
}

void AnimatedSprite::pause()
{
	m_status = Paused;
}

void AnimatedSprite::stop()
{
	m_status = Stopped;
	m_currentFrame = 0;
	setFrame( 0, true );
}

AnimatedSprite::Status AnimatedSprite::getStatus() const
{
	return m_status;
}

//

void AnimatedSprite::setFrame( size_t index )
{
	assert( m_animation );
	m_currentFrame = index % m_animation->size();
	setFrame( m_currentFrame, true ); /**/
}

void AnimatedSprite::setColor( const sf::Color& color )
{
	m_vertices[ 0 ].color = color;
	m_vertices[ 1 ].color = color;
	m_vertices[ 2 ].color = color;
	m_vertices[ 3 ].color = color;
}

void AnimatedSprite::update( const sf::Time& delta )
{
	if ( m_status == Playing and m_animation )
	{
		m_elapsed += delta;

		if ( m_elapsed > m_delta )
		{
			m_elapsed -= m_delta;
			if ( m_currentFrame + 1 < m_animation->size() )
				m_currentFrame++;
			else
			{
				m_currentFrame = 0;

				if ( !m_loop )
				{
					--m_repeat;
					if ( m_repeat <= 0 )
					{
						m_status = Stopped;
						onFinished();
					}
				}
			}
		}

		setFrame( m_currentFrame, false );
	}
}

void AnimatedSprite::setFrame( size_t index, bool resetTime )
{
	if ( m_animation )
	{
		sf::IntRect rect = m_animation->getRect( index );

		//vertice positions
		m_vertices[ 0 ].position = sf::Vector2f( 0.f,								 0.f								 );
		m_vertices[ 1 ].position = sf::Vector2f( 0.f,								 static_cast< float >( rect.height ) );
		m_vertices[ 2 ].position = sf::Vector2f( static_cast< float >( rect.width ), static_cast< float >( rect.height ) );
		m_vertices[ 3 ].position = sf::Vector2f( static_cast< float >( rect.width ), 0.f								 );

		//texture coords
		float left   = static_cast< float >( rect.left );
		float right  = left + static_cast< float >( rect.width );
		float top    = static_cast< float >( rect.top );
		float bottom = top + static_cast< float >( rect.height );

		m_vertices[ 0 ].texCoords = sf::Vector2f( left,  top );
		m_vertices[ 1 ].texCoords = sf::Vector2f( left,  bottom );
		m_vertices[ 2 ].texCoords = sf::Vector2f( right, bottom );
		m_vertices[ 3 ].texCoords = sf::Vector2f( right, top );
	}

	if ( resetTime )
		m_elapsed = sf::Time::Zero;
}

void AnimatedSprite::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
	if ( m_animation and m_animation->m_texture )
	{
		states.transform *= getTransform();
		states.texture = m_animation->m_texture;
		target.draw( m_vertices, 4, sf::Quads, states );
	}
}