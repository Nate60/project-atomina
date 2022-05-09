#pragma once

#include "../pch.hpp"
#include "../core/api.hpp"
#include "State.hpp"
#include "../util/Log.hpp"

namespace ATMA {


	using StateType = unsigned int;

	class StateManager;
	class ATMA_API BaseState
	{


	public:
		BaseState(StateManager &l_stateMan);
		BaseState(BaseState &&b) noexcept;


		virtual ~BaseState();

		virtual void onCreate() = 0;
		virtual void onDestroy() = 0;
		virtual void activate() = 0;
		virtual void deactivate() = 0;

		virtual void update(const sf::Time& l_time) = 0;
		virtual void draw() = 0;

		virtual StateType getId() const
		{
			return static_cast<StateType>(State::Empty);
		}

		sf::View& getView();

		bool operator == (const BaseState &b) const;
		bool operator < (const BaseState &b) const;
		bool operator > (const BaseState &b) const;

	protected:

		StateManager &m_stateMan;
		bool m_transparent;
		bool m_transcendent;
		bool m_communicable;

		sf::View m_view;

	};


}
