#pragma once
#include "pch.h"
#include "api.h"
#include "AttrBase.h"

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
