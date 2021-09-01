#pragma once

#include "animation.hpp"

#include < SFML/Graphics/Drawable.hpp >
#include < SFML/Graphics/Transformable.hpp >
#include < SFML/Graphics/RenderTarget.hpp >
#include < SFML/Graphics/RenderStates.hpp >
#include < SFML/System/Time.hpp >

#include < functional >

class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
public:
	AnimatedSprite( const AnimatedSprite& ) = default;
	AnimatedSprite& operator = ( const AnimatedSprite& ) = default;
	AnimatedSprite( AnimatedSprite&& ) = default;
	AnimatedSprite& operator = ( AnimatedSprite&& ) = default;

	using FunctionType = std::function< void() >;
	static FunctionType defaultFunction;
	FunctionType onFinished;
	enum Status
	{
		Stopped,
		Paused,
		Playing
	};

	AnimatedSprite( Animation* animation = nullptr, 
					Status status = Playing,
					const sf::Time& delta = sf::seconds( 0.15 ),
					bool loop = true,
					int repeat = 0								 );

	void setAnimation( Animation* animation );
	Animation* getAnimation() const;

	void setFrameTime( sf::Time delta );
	sf::Time getFrameTime() const;

	void setLoop( bool loop );
	bool getLoop() const;
	void setRepeat( int rptnmb );
	int getRepeat() const;

	void play();
	void pause();
	void stop();
	Status getStatus() const;

	void setFrame( size_t index );
	void setColor( const sf::Color& color );
	void update( const sf::Time& delta );

private:
	Animation* m_animation;
	sf::Time m_delta;
	sf::Time m_elapsed;

	bool m_loop;
	int m_repeat;

	Status m_status;
	size_t m_currentFrame;
	sf::Vertex m_vertices[ 4 ];

private:
	void setFrame( size_t index, bool resetTime );

	virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
};
