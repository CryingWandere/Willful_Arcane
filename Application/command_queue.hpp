#pragma once

#include "command.hpp"

#include < queue >

class CommandQueue
{
public:
	void add( const Command& command );
	Command remove();

	bool isEmpty() const;

private:
	std::queue< Command > m_queue;
};