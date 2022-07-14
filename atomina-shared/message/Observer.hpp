#pragma once
#include "../core/api.hpp"
#include "../pch.hpp"
namespace ATMA {

	using Message = std::string;

	class ATMA_API Observer {
	public:
		virtual ~Observer() {}
		virtual void notify(const Message& l_message) = 0;
	};

}