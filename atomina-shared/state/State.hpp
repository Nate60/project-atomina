#pragma once

#include "../pch.hpp"
#include "../core/api.hpp"

namespace ATMA 
{

	enum class ATMA_API State
	{
		Empty = 0u,
		Dummy = 1u,
		COUNT
	};

	class ATMA_API StateType{
	public:
		StateType(const State &l_type): m_type(l_type)
		{}

		//conversion constructor
		StateType(const unsigned int &l_int): m_type(static_cast<State>(l_int))		
		{}

		//conversion operator
		operator unsigned int()
		{
			return static_cast<unsigned int>(m_type);
		}

	private:
		const State m_type;
	};

}
