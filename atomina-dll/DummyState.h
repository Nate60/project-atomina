#pragma once
#include "BaseState.h"

namespace ATMA
{
	class ATMA_API DummyState: public BaseState
	{
	public:

		DummyState();

		virtual ~DummyState();

		virtual void onCreate();
		virtual void onDestroy();
		virtual void activate();
		virtual void deactivate();

		virtual StateType getId() const override
		{
			return static_cast<StateType>(State::Dummy);
		}

		virtual void update(const sf::Time &l_time);
		virtual void draw();

	};
}