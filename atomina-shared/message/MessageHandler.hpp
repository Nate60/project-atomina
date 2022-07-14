#pragma once
#include "../core/api.hpp"
#include "../OAS/ObjectMessage.hpp"
#include "Observer.hpp"
#include "Communicator.hpp"
#include "../pch.hpp"

namespace ATMA {

	class ATMA_API MessageHandler {
		using Message = std::string;
		using Subscriptions = std::unordered_map<ObjectMessage, Communicator>;
	public:
		bool subscribe(const ObjectMessage& l_type, std::shared_ptr<Observer> l_observer);

		bool unsubscribe(const ObjectMessage& l_type, std::shared_ptr<Observer> l_observer);

		void dispatch(const Message& l_msg);

	private:
		Subscriptions m_communicators;

	};

}