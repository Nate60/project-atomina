#include "pch.h"
#include "StateManager.h"

namespace ATMA {

	StateManager::StateManager()
	{

	}


	StateManager::~StateManager()
	{
		purge();
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


	bool StateManager::hasState(const State& l_type) const
	{
		auto result = std::find_if(m_states.begin(), m_states.end(), [&l_type](auto state)
			{
				return state->getId() == l_type;
			}
		);
		return result != m_states.end();

	}

	std::optional<State> StateManager::getNextToLast() const
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

	void StateManager::changeState(const State& l_type)
	{

	}

	void StateManager::remove(const State& l_type)
	{
		auto result = std::find_if(m_states.begin(), m_states.end(), [&l_type](auto state)
			{
				return state->getId() == l_type;
			}
		);
		if(result != m_states.end())
		{
			m_states.erase(result);
		}
	}


	void StateManager::purge()
	{
		m_states.clear();
	}
}