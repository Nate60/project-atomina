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

		virtual State getId() const override
		{
			return State::Dummy;
		}

		virtual void update(const sf::Time &l_time);
		virtual void draw();

	};
}