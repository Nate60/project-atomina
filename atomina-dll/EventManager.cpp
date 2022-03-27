#include "pch.h"
#include "EventManager.h"

namespace ATMA {

	EventManager::EventManager()
	{}

	//EventManager::EventManager(EventManager &&other)
	//{
	//	m_bindings = std::move(other.m_bindings);
	//	m_callbacks = std::move(other.m_callbacks);
	//}

	EventManager::~EventManager()
	{}

	bool EventManager::addBinding(const std::string &l_name, std::shared_ptr<Binding> l_binding)
	{
		m_bindings[l_name] = std::move(l_binding);
		return true;
	}

	bool EventManager::removeBinding(std::string l_name)
	{
		m_bindings.erase(l_name);
		return true;
	}

	void EventManager::onCreateState(const StateType &l_type)
	{

	}

	void EventManager::onStateChange(const StateType &l_type)
	{

	}

	void EventManager::onStateRemove(const StateType& l_type)
	{

	}

	bool EventManager::removeCallBack(const std::string& l_name, const StateType& l_type)
	{
		return false;
	}

	void EventManager::handleEvent(Event& l_event)
	{
		auto itr = m_callbacks.find(m_currentState);
		
		auto &callback = itr->second.find(l_event.m_type)->second;
		callback(l_event);

	}

	void EventManager::update()
	{

	}

}