#pragma once
#include "../../pch.hpp"
#include "../../core/api.hpp"
#include "../AttrBase.hpp"

namespace ATMA
{

	class ATMA_API AttrControllable: public AttrBase
	{
	public:
		AttrControllable();
		~AttrControllable();

		void readIn(std::stringstream &l_stream) override;

	};

}
