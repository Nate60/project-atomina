#include "pch.h"
#include "StateManager.h"

namespace ATMA {

	StateManager::StateManager(ATMAContext &l_ctx): m_context(l_ctx)
	{

	}


	StateManager::~StateManager()
	{
		purge();
	}

	void StateManager::addStateDependent(std::shared_ptr<StateSensitive> l_dep)
	{
		m_deps.push_back(l_dep);
	}

	void StateManager::removeStateDependent(std::shared_ptr<StateSensitive> l_dep)
	{
		
	}

	void StateManager::update(const sf::Time& l_time)
	{
		std::for_each(std::execution::par, m_states.begin(), m_states.end(), [&l_time](auto state)
			{
				state->update(l_time);
			}
		);

	}

	void StateManager::draw()
	{
		std::for_each(std::execution::seq, m_states.begin(), m_states.end(), [](auto state)
			{
				state->draw();
			}
		);
	}

	bool StateManager::hasState(const State &l_type) const
	{
		return hasState(static_cast<StateType>(l_type));

	}

	bool StateManager::hasState(const StateType &l_type) const
	{
		auto result = std::find_if(m_states.begin(), m_states.end(), [&l_type](auto state)
			{
				return state->getId() == l_type;
			}
		);
		return result != m_states.end();

	}

	std::optional<StateType> StateManager::getNextToLast() const
	{
		try
		{
			auto itr = (m_states.end() - 2);
			return (*itr)->getId();
		}
		catch (std::exception &e)
		{
			ATMA_ENGINE_WARN("attempt to get next to last state when it does not exist: {}", e.what());
			return std::nullopt;
		}

	}

	void StateManager::changeState(const StateType &l_type)
	{
		
	}

	bool StateManager::remove(const State &l_type)
	{
		return remove(static_cast<StateType>(l_type));
	}

	bool StateManager::remove(const StateType &l_type)
	{
		auto result = std::find_if(m_states.begin(), m_states.end(), [&l_type](auto state)
			{
				return state->getId() == l_type;
			}
		);
		if(result != m_states.end())
		{
			ATMA_ENGINE_INFO("Removed state of type {0:d}", l_type);
			m_states.erase(result);
			return true;
		}
		else
		{
			ATMA_ENGINE_WARN("Unable to remove state of type {0:d} as it does not exist", l_type);
			return false;
		}
	}

	ATMAContext &StateManager::getContext()
	{
		return m_context;
	}

	void StateManager::purge()
	{
		ATMA_ENGINE_INFO("Clearing states..");
		m_states.clear();
	}
}