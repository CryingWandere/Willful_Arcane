#pragma once

#include < string >
#include < map >
#include < memory >

#include < stdexcept >
#include < cassert >


template < typename Resource, typename Identifier >
class ResourceHolder
{
public:
	void load( Identifier id, const std::string& fileName );

	template < typename Parameter >
	void load ( Identifier id, const std::string& fileName, const Parameter& secondParameter );
	//
	Resource& get( Identifier id );
	const Resource& get( Identifier id ) const;

private:
	void addResource( Identifier id, std::unique_ptr< Resource > resource );
	//
private:
	std::map< Identifier, std::unique_ptr< Resource > > m_resourceMap;

};

#include "resource_holder.inl"