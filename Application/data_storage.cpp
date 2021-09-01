#include "data_storage.hpp"

#include "hero.hpp"
#include "enemy.hpp"
#include "npc.hpp"

#include "weapon.hpp"

std::vector< HeroData > initializeHeroData()
{
	std::vector< HeroData > data( Hero::AllHeroes );

	//	Warrior
	data[ Hero::Warrior ].hitpoints =				100;
	data[ Hero::Warrior ].speed =					600.f;
	data[ Hero::Warrior ].attackCooldown =			sf::milliseconds( 400 );
	data[ Hero::Warrior ].texture =					Textures::Oleg;
	data[ Hero::Warrior ].textureRect =				sf::IntRect( 0, 0, 65, 120 );
	data[ Hero::Warrior ].mirroredTextureRect =		sf::IntRect( 65, 0, -65, 120 );
	data[ Hero::Warrior ].b_hasRotateAnimation =	true;
	data[ Hero::Warrior ].b_hasDefaultAnimation =	true;
	data[ Hero::Warrior ].b_hasWalkingAnimation =	true;
	data[ Hero::Warrior ].b_hasAttackAnimation =	true;

	//	Archer
	data[ Hero::Archer ].hitpoints =				100;
	data[ Hero::Archer ].speed =					600.f;
	data[ Hero::Archer ].attackCooldown =			sf::milliseconds( 400 );
	data[ Hero::Archer ].texture =					Textures::Oleg;
	data[ Hero::Archer ].textureRect =				sf::IntRect( 0, 0, 65, 120 );
	data[ Hero::Archer ].b_hasRotateAnimation =		true;
	data[ Hero::Archer ].b_hasDefaultAnimation =	true;
	data[ Hero::Archer ].b_hasWalkingAnimation =	true;
	data[ Hero::Archer ].b_hasAttackAnimation =		true;

	//	Wizard
	data[ Hero::Wizard ].hitpoints =				100;
	data[ Hero::Wizard ].speed =					600.f;
	data[ Hero::Wizard ].attackCooldown =			sf::milliseconds( 400 );
	data[ Hero::Wizard ].texture =					Textures::Oleg;
	data[ Hero::Wizard ].textureRect =				sf::IntRect( 0, 0, 65, 120 );
	data[ Hero::Wizard ].b_hasRotateAnimation =		true;
	data[ Hero::Wizard ].b_hasDefaultAnimation =	true;
	data[ Hero::Wizard ].b_hasWalkingAnimation =	true;
	data[ Hero::Wizard ].b_hasAttackAnimation =		true;

	return data;
}

std::vector< EnemyData > initializeEnemyData()
{
	std::vector< EnemyData > data( Enemy::AllEnemies );

	//	Basic Enemy
	data[ Enemy::BasicGuided ].hitpoints =				70;
	data[ Enemy::BasicGuided ].speed =					480.f;
	data[ Enemy::BasicGuided ].attackCooldown =			sf::milliseconds( 600 );
	data[ Enemy::BasicGuided ].texture =				Textures::UndeadOld;
	data[ Enemy::BasicGuided ].textureRect =			sf::IntRect( 0, 0, 65, 120 );
	data[ Enemy::BasicGuided ].mirroredTextureRect =	sf::IntRect( 65, 0, -65, 120 );
	data[ Enemy::BasicGuided ].b_hasRotateAnimation =	true;

	return data;
}

std::vector< NPCData > initializeNPCData()
{
	std::vector< NPCData > data( NPC::AllNPCs );

	data[ NPC::PeasantGirl ].hitpoints =				999999;
	data[ NPC::PeasantGirl ].texture =					Textures::PeasantGirl;
	data[ NPC::PeasantGirl ].textureRect =				sf::IntRect( 0, 0, 65, 120 );
	data[ NPC::PeasantGirl ].mirroredTextureRect =		sf::IntRect( 65, 0, -65, 120 );

	return data;
}

std::vector< WeaponData > initializeWeaponData()
{
	std::vector< WeaponData > data( Weapon::Total );

	data[ Weapon::Sword ].damage =						4; //*7
	data[ Weapon::Sword ].texture =						Textures::Sword;

	data[ Weapon::EnemySword ].damage =					2; //*7
	data[ Weapon::EnemySword ].texture =				Textures::Sword;

	return data;
}