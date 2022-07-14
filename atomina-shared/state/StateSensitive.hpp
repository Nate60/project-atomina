#pragma once
#include "../pch.hpp"
#include "../core/api.hpp"


namespace ATMA
{
	using StateType = unsigned int;
	class ATMA_API StateSensitive
	{
	public:
		virtual void onStateCreate(const StateType &l_type) = 0;
		virtual void onStateChange(const StateType &l_type) = 0;
		virtual void onStateRemove(const StateType &l_type) = 0;
	protected:
		void notifyCurrentState(const StateType &l_type)
		{
			m_currentState = l_type;
		}
		StateType m_currentState{0u};
	};
}
