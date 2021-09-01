#include "command_queue.hpp"

void CommandQueue::add( const Command& command )
{
	m_queue.push( command );
}

Command CommandQueue::remove()
{
	Command command = m_queue.front();
	m_queue.pop();

	return command;
}

bool CommandQueue::isEmpty() const
{
	return m_queue.empty();
}