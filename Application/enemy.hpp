#pragma once

#include "entity.hpp"
#include "command.hpp"
#include "command_queue.hpp"
#include "resource_identify.hpp"
#include "text_node.hpp"
#include "weapon.hpp"

#include < SFML/Graphics/Sprite.hpp >

class Enemy : public Entity
{
public:
	enum Type
	{
		BasicGuided,

		AllEnemies
	};

public:
	Enemy( Type type, const TextureHolder& textures, const FontHolder& fonts );

	void guideTowards( sf::Vector2f position );
	bool isGuided() const;

	virtual unsigned int getCategory() const;
	virtual sf::FloatRect getBoundingRect() const;
	virtual bool isMarkedForRemoval() const;

	float getMaxSpeed() const;

	void attack();

private:
	virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;
	virtual void updateCurrent( sf::Time delta, CommandQueue& commands );
	void updateMovementPattern( sf::Time delta );

	void updateEnemyDirection();

	void updateText();

	void checkAttack( sf::Time delta, CommandQueue& commands );
	void createAttack( SceneNode& node, const TextureHolder& textures ) const;
	void createWeapon( SceneNode& node, Weapon::Type type, float xOffset, float yOffset, bool invert, const TextureHolder& textures ) const;

private:
	Type m_type;

	sf::Sprite m_sprite;

	Command m_attackCommand;

	float m_travelledDistance;
	std::size_t m_directionIndex;
	TextNode* m_healthDisplay;

	sf::Vector2f m_targetDirection;

	sf::Time m_attackCooldown;
	sf::Time m_movementCooldown;
	sf::Time m_stopCooldown;
	sf::Time m_second;

	bool m_b_last;

	bool m_b_isMarkedForRemoval;
	bool m_b_isAttacking;
};