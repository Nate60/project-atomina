#pragma once

#include "pch.h"
#include "api.h"
#include "State.h"
#include "BaseState.h"
#include "StateSensitive.h"
#include "ATMAContext.h"


namespace ATMA
{


	/*
	* Manager for updating, drawing, and switching states
	*/

	using StateContainer = std::vector<std::shared_ptr<BaseState>>;
	using StateDependents = std::vector<std::shared_ptr<StateSensitive>>;
	using StateType = unsigned int;

	class ATMA_API StateManager
	{
	public:

		StateManager(ATMAContext &l_ctx);
		~StateManager();

		void addStateDependent(std::shared_ptr<StateSensitive> l_dep);

		void removeStateDependent(std::shared_ptr<StateSensitive> l_dep);

		/*
		* updates all active states
		* @param time since last update
		*/
		void update(const sf::Time& l_time);

		/*
		* calls draw for each active an non-transparent state
		*/
		void draw();

		/*
		* checks for state in manager
		* @param State type enum
		* @return if it is found or not
		*/
		bool hasState(const State &l_type) const;

		/*
		* checks for state in manager
		* @param State type enum
		* @return if it is found or not
		*/
		bool hasState(const StateType &l_type) const;

		/*
		* get second highest priority state
		* @return type of state
		*/
		std::optional<StateType> getNextToLast() const;

		/*
		* moves state to front
		* @param type of state
		*/
		void changeState(const StateType &l_type);

				/*
		* removes the specified state type from the manager
		* @param type of state
		*/
		bool remove(const State &l_type);

		/*
		* removes the specified state type from the manager
		* @param type of state
		*/
		bool remove(const StateType &l_type);

		/*
		* returns the state object of a given state type
		* @param type of the state
		* @return state object
		*/
		template <class T>
		std::shared_ptr<T> getState(const StateType &l_type)
		{
			if constexpr(std::is_base_of_v<BaseState, T>)
			{
				auto result = std::find_if(m_states.begin(), m_states.end(), [&l_type](auto state)
					{
						return state->getId() == l_type;
					}
				);
				if(result == m_states.end())
					throw ValueNotFoundException("State of type " + std::to_string(l_type) + " not found");
				return result;
			}
			else
			{
				throw std::bad_cast("unable to cast as type is not subclass of BaseState");
			}

		}

		/*
		* registers the state to the manager
		* @param type of state to register
		*/
		template <class T>
		bool registerState(const State &l_type)
		{
			return registerState<T>(static_cast<StateType>(l_type));
		}
	
		/*
		* registers the state to the manager
		* @param type of state to register
		*/
		template <class T>
		bool registerState(const StateType &l_type)
		{
			if constexpr (std::is_base_of_v<BaseState, T>)
			{
				auto result = std::find_if(m_states.begin(), m_states.end(), [&l_type](auto state)
					{
						return state->getId() == l_type;
					}
				);
				if(result == m_states.end())
				{
					m_states.emplace_back(std::shared_ptr<T>{new T{*this}});
					if(auto state = m_states.back(); state->getId() != l_type)
					{
						m_states.pop_back();
						ATMA_ENGINE_WARN("Unable to register state of type {0:d} as it does not match type of state class", l_type);
						return false;
					}
					else
					{
						state->onCreate();
						ATMA_ENGINE_INFO("Registered state of type {0:d}", l_type);
						return true;
					}
				}
				else
				{
					ATMA_ENGINE_WARN("Unable to register state of type {0:d} as it already exists", l_type);
					return false;
				}

			}
			else
			{
				ATMA_ENGINE_WARN("Unable to register state of type {0:d} as class type is not subclass of BaseState", l_type);
				return false;
			}

		}

		ATMAContext &getContext();


		/*
		* removes all states from the manager
		*/
		void purge();


	private:

		StateContainer m_states;
		StateDependents m_deps;
		ATMAContext m_context;



	};

}
