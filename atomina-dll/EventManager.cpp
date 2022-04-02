#include "pch.h"
#include "EventManager.h"

namespace ATMA {

	EventManager::EventManager()
	{}

	EventManager::~EventManager()
	{}

	bool EventManager::addBinding(const std::string &l_name, std::shared_ptr<Binding> l_binding)
	{
		if(m_bindings.find(l_name) == m_bindings.end())
		{
			m_bindings[l_name] = std::move(l_binding);
			ATMA_ENGINE_INFO("Added binding {}", l_name);
			return true;
		}
		ATMA_ENGINE_WARN("Unable to add binding with name {} as it already exists", l_name);
		return false;

	}

	bool EventManager::removeBinding(const std::string &l_name)
	{
		
		if(m_bindings.erase(l_name))
		{
			ATMA_ENGINE_INFO("Removed binding {}", l_name);
			return true;
		}
		return false;
	}

	void EventManager::onStateCreate(const StateType &l_type)
	{

	}

	void EventManager::onStateChange(const StateType &l_type)
	{

	}

	void EventManager::onStateRemove(const StateType &l_type)
	{

	}

	bool EventManager::removeCallBack(const EventType &l_event_type, const StateType &l_type)
	{
		if(l_type == 0u && m_currentState != 0)
			return removeCallBack(l_event_type, m_currentState);
		if(m_callbacks.find(l_type) == m_callbacks.end())
		{
			ATMA_ENGINE_WARN("Unable to remove callback for event type {0:d} in state type {1:d} as it does not exists", l_event_type, l_type);
			return false;
		}
		else if(m_callbacks[l_type].find(l_event_type) == m_callbacks[l_type].end())
		{
			ATMA_ENGINE_WARN("Unable to remove callback for event type {0:d} in state type {1:d} as it does not exists", l_event_type, l_type);
			return false;
		}
		else
		{
			m_callbacks[l_type].erase(l_event_type);
			ATMA_ENGINE_INFO("Removed callback for event type {0:d} in state type {1:d}", l_event_type, l_type);
			return true;
		}
	}

	bool EventManager::addCallBack(const EventType &l_event_type, std::function<void(Event &)> l_func, const StateType &l_type)
	{
		if(l_type == 0u && m_currentState != 0)
			return addCallBack(l_event_type, l_func, m_currentState);
		if(m_callbacks.find(l_type) == m_callbacks.end())
		{
			m_callbacks[l_type] = std::move(CallbackContainer{{l_event_type, l_func}});
			ATMA_ENGINE_INFO("Added callback for event type {0:d} in state type {1:d}", l_event_type, l_type);
			return true;
		}
		else if(m_callbacks[l_type].find(l_event_type) == m_callbacks[l_type].end())
		{
			m_callbacks[l_type][l_event_type] = l_func;
			ATMA_ENGINE_INFO("Added callback for event type {0:d} in state type {1:d}", l_event_type, l_type);
			return true;
		}
		else
		{
			ATMA_ENGINE_WARN("Unable to add callback for event type {0:d} in state type {1:d} as it already exists", l_event_type, l_type);
			return false;
		}


	}

	void EventManager::handleEvent(Event& l_event)
	{
		auto itr = m_callbacks.find(m_currentState);
		
		if(itr == m_callbacks.end())
		{
			throw ValueNotFoundException("Cannot handle event as there is no callback for state " + std::to_string(m_currentState));
		}

		auto itr2 = itr->second.find(l_event.m_type);

		if(itr2 == itr->second.end())
		{
			throw ValueNotFoundException("Cannot handle event as there is no callback for event type " + std::to_string(l_event.m_type));
		}

		ATMA_ENGINE_INFO("Calling callback for event type {0:d} for state type {1:d}", l_event.m_type, m_currentState);
		auto &callback = itr2->second;
		callback(l_event);

	}

	void EventManager::update()
	{

	}

}