#include "../pch.hpp"
#include "MessageHandler.hpp"

namespace ATMA
{
	
	bool MessageHandler::subscribe(const ObjectMessage &l_type, std::shared_ptr<Observer> l_observer)
	{
		if(auto itr = m_communicators.find(l_type); itr == m_communicators.end())
		{
			m_communicators[l_type] = Communicator{};
			m_communicators[l_type].addOverserver(l_observer);
			return true;
		}
		else if(itr->second.hasObserver(l_observer))
		{
			return false;
		}
		else
		{
			itr->second.addOverserver(l_observer);
			return true;
		}
	}

	bool MessageHandler::unsubscribe(const ObjectMessage &l_type, std::shared_ptr<Observer> l_observer)
	{
		if(auto itr = m_communicators.find(l_type); itr == m_communicators.end())
		{
			return false;
		}
		else if(itr->second.hasObserver(l_observer))
		{
			itr->second.removeObserver(l_observer);
			return true;
		}
		else
		{
			return false;
		}
	}

	void MessageHandler::dispatch(const Message &l_msg)
	{
		for(auto &communicator : m_communicators)
		{
			communicator.second.broadcast(l_msg);
		}
	}
}