#pragma once

#include "pch.h"
#include "api.h"
#include "State.h"
#include "Log.h"

namespace ATMA {

	class ATMA_API BaseState
	{
	public:
		BaseState();
		BaseState(BaseState &&b) noexcept;


		virtual ~BaseState();

		virtual void onCreate() = 0;
		virtual void onDestroy() = 0;
		virtual void activate() = 0;
		virtual void deactivate() = 0;

		virtual void update(const sf::Time& l_time) = 0;
		virtual void draw() = 0;

		virtual State getId() const
		{
			return State::Empty;
		}

		sf::View& getView();

		bool operator == (const BaseState &b) const;
		bool operator < (const BaseState &b) const;
		bool operator > (const BaseState &b) const;

	protected:

		bool m_transparent;
		bool m_transcendent;
		bool m_communicable;

		sf::View m_view;

	};


}
