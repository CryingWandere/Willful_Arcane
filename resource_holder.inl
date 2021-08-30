//________________________________________________________\\
//

template < typename Resource, typename Identifier >
void ResourceHolder< Resource, Identifier >::load( Identifier id, const std::string& fileName )
{
	std::unique_ptr< Resource > resource( new Resource() );

	if ( !resource->loadFromFile( fileName ) )
		throw std::runtime_error( "ResourceHolder failed to load " + fileName );

	auto inserted = m_resourceMap.insert( std::make_pair( id, std::move( resource ) ) );
	assert( inserted.second );
}

template < typename Resource, typename Identifier >
template < typename Parameter >
void ResourceHolder< Resource, Identifier >::load( Identifier id, const std::string& fileName, const Parameter& secondParameter )
{
	std::unique_ptr< Resource > resource( new Resource() );
	
	if ( !resource->loadFromFile( fileName, secondParameter ) )
		throw std::runtime_error( "ResourceHolder failed to load " + fileName );

	addResource( id, std::move( resource ) );
}

template < typename Resource, typename Identifier >
Resource& ResourceHolder< Resource, Identifier >::get( Identifier id )
{
	auto find = m_resourceMap.find( id );
	assert( find != m_resourceMap.end() );

	return *find->second;
}

template < typename Resource, typename Identifier >
const Resource& ResourceHolder< Resource, Identifier >::get( Identifier id ) const
{
	auto find = m_resourceMap.find( id );
	assert( find != m_resourceMap.end() );

	return *find->second;
}

template < typename Resource, typename Identifier >
void ResourceHolder< Resource, Identifier >::addResource( Identifier id, std::unique_ptr< Resource > resource )
{
	auto added = m_resourceMap.insert( std::make_pair( id, std::move( resource ) ) );
	assert( added.second );
}