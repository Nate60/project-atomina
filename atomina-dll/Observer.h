#pragma once
#include "api.h"
#include "pch.h"
namespace ATMA {

	using Message = std::string;

	class ATMA_API Observer {
	public:
		virtual ~Observer() {}
		virtual void notify(const Message& l_message) = 0;
	};

}