#pragma once

#include "resource_identify.hpp"

#include < SFML/System/Time.hpp >
#include < SFML/Graphics/Color.hpp >
#include < SFML/Graphics/Rect.hpp >

#include < vector >

//FORWARD DECLARATION
class Hero;

struct Direction
{
	Direction( float angle, float distance )
		:	angle( angle )
		,	distance( distance )
	{
	}

	float angle;
	float distance;
};

struct HeroData
{
	int hitpoints;
	float speed;

	Textures::ID texture;

	sf::IntRect textureRect;
	sf::IntRect mirroredTextureRect;

	sf::Time attackCooldown;
	//std::vector<Direction> directions;

	bool b_hasRotateAnimation;
	bool b_hasDefaultAnimation;
	bool b_hasWalkingAnimation;
	bool b_hasAttackAnimation;
};

struct EnemyData
{
	int hitpoints;
	float speed;

	Textures::ID texture;

	sf::IntRect textureRect;
	sf::IntRect mirroredTextureRect;

	sf::Time attackCooldown;
	std::vector< Direction > directions;

	bool b_hasRotateAnimation;
};

struct NPCData
{
	int hitpoints;

	Textures::ID texture;

	sf::IntRect textureRect;
	sf::IntRect mirroredTextureRect;
};

struct WeaponData
{
	int damage;
	Textures::ID texture;
};

std::vector< HeroData > initializeHeroData();
std::vector< EnemyData > initializeEnemyData();
std::vector< NPCData > initializeNPCData();

std::vector< WeaponData > initializeWeaponData();