#pragma once

#include "entity.hpp"
#include "command.hpp"
#include "command_queue.hpp"
#include "resource_identify.hpp"
#include "text_node.hpp"
#include "weapon.hpp"

#include <SFML/Graphics/Sprite.hpp>

class Hero : public Entity
{
public:
	enum Type
	{
		Warrior,
		Archer,
		Wizard,

		AllHeroes
	};

public:
	Hero( Type type, const TextureHolder& textures, const FontHolder& fonts );
	
	virtual unsigned int getCategory() const;
	virtual sf::FloatRect getBoundingRect() const;
	virtual bool isMarkedForRemoval() const;

	float getMaxSpeed() const;

	void setTextVisibility( bool b_visible );
	bool getTextVisibility() const;

	void setAttack( bool attack );
	bool getAttack() const;

	void interact();
	void attack();

private:
	virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;
	virtual void updateCurrent( sf::Time delta, CommandQueue& commands );

	void updateHeroDirection();

	void updateText();

	void checkInteraction( sf::Time delta, CommandQueue& commands );
	void createInteraction() const;

	void checkAttack( sf::Time delta, CommandQueue& commands );
	void createAttack( SceneNode& node, const TextureHolder& textures ) const;
	void createWeapon( SceneNode& node, Weapon::Type type, float xOffset, float yOffset, bool invert, const TextureHolder& textures ) const;

private:
	Type m_type;

	sf::Sprite m_sprite;

	Command m_interactCommand;
	Command m_attackCommand;

	TextNode* m_healthDisplay;

	sf::Time m_attackCooldown;
	sf::Time m_healCooldown;

	bool m_b_isTextVisible;
	bool m_b_isAttackRequired;

	bool m_b_last;

	bool m_b_isInteracting;
	bool m_b_isAttacking;
	bool m_b_isMarkedForRemoval;
};
