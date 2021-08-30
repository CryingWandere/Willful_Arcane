#include "scene_node.hpp"

#include "command.hpp"
#include "utilities.hpp"

#include < cassert >

SceneNode::SceneNode()
	:	m_children()
	,	m_parent( nullptr )
{
}

void SceneNode::attachChild( Pointer child )
{
	child->m_parent = this;
	m_children.push_back( std::move( child ) );
}

SceneNode::Pointer SceneNode::detachChild( const SceneNode& node )
{
	auto find = std::find_if( m_children.begin(), m_children.end(), [&] ( Pointer& ptr ) -> bool { return ptr.get() == &node; } );

	assert( find != m_children.end() );

	Pointer result = std::move( *find );
	result->m_parent = nullptr;
	m_children.erase( find );
	return result;
}

void SceneNode::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
	states.transform *= getTransform();

	drawCurrent( target, states );
	drawChildren( target, states );
}

void SceneNode::drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const
{
	//Do nothing
}

void SceneNode::drawChildren( sf::RenderTarget& target, sf::RenderStates states ) const
{
	for ( const Pointer& child : m_children )
	{
		child->draw( target, states );
	}
}

void SceneNode::update( sf::Time delta, CommandQueue& commands )
{
	updateCurrent( delta, commands );
	updateChildren( delta, commands );
}

void SceneNode::updateCurrent( sf::Time delta, CommandQueue& commands )
{
	//Do nothing
}

void SceneNode::updateChildren( sf::Time delta, CommandQueue& commands )
{
	for ( const Pointer& child : m_children )
	{
		child->update( delta, commands );
	}
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for ( const SceneNode* node = this; node != nullptr; node = node->m_parent )
		transform = node->getTransform() * transform;

	return transform;
}

void SceneNode::onCommand( const Command& command, sf::Time delta )
{
	//Current node
	if ( command.category & getCategory() )
		command.action( *this, delta );

	//Children
	for ( Pointer& child : m_children )
	{
		child->onCommand( command, delta );
	}
}

unsigned int SceneNode::getCategory() const
{
	return Category::Scene;
}

void SceneNode::checkSceneCollision( SceneNode& sceneGrath, std::set< Pair >& collisionPairs )
{
	checkNodeCollision( sceneGrath, collisionPairs );

	for( Pointer& child : sceneGrath.m_children )
		checkSceneCollision( *child, collisionPairs );
}

void SceneNode::checkNodeCollision( SceneNode& node, std::set< Pair >& collisionPairs )
{
	if ( this != &node && collision( *this, node ) )
		collisionPairs.insert( std::minmax( this, &node ) );

	for( Pointer& child : m_children )
		child->checkNodeCollision( node, collisionPairs );
}

void SceneNode::removeCorpses()
{
	auto corpsefieldBegin = std::remove_if( m_children.begin(), m_children.end(), std::mem_fn( &SceneNode::isMarkedForRemoval ) );
	m_children.erase( corpsefieldBegin, m_children.end() );

	std::for_each( m_children.begin(), m_children.end(), std::mem_fn( &SceneNode::removeCorpses ) );
}

sf::FloatRect SceneNode::getBoundingRect() const
{
	return sf::FloatRect();
}

bool SceneNode::isMarkedForRemoval() const
{
	//By default
	return isDestroyed();
}

bool SceneNode::isDestroyed() const
{
	//By default
	return false;
}

bool collision( const SceneNode& first, const SceneNode& second )
{
	return first.getBoundingRect().intersects( second.getBoundingRect() );
}

float distance( const SceneNode& first, const SceneNode& second )
{
	return length( first.getWorldPosition() - second.getWorldPosition() );
}