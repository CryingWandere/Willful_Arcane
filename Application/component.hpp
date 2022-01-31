#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>

//Forward declaration
namespace sf
{
	class Event;
}

namespace GUI
{
class Component : public sf::Drawable, public sf::Transformable, public sf::NonCopyable
{
public:
	typedef std::shared_ptr< Component > Pointer;

public:
	Component();
	virtual ~Component();

	virtual bool isSelectable() const = 0;
	bool isSelected() const;

	virtual void select();
	virtual void deselect();

	virtual bool isActive() const;

	virtual void activate();
	virtual void deactivate();

	virtual void handleEvent( const sf::Event& sfevent ) = 0;

private:
	bool m_isSelected;
	bool m_isActive;
};

}
