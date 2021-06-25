#pragma once
#include "api.h"
#include "ObjectMessage.h"
#include "Observer.h"
#include "Communicator.h"
#include <string>
#include <unordered_map>

namespace ATMA {

	class ATMA_API MessageHandler {
		using Message = std::string;
		using Subscriptions = std::unordered_map<ObjectMessage, Communicator>;
	public:
		bool subscribe(const ObjectMessage& l_type, Observer* l_observer);

		bool unsubscribe(const ObjectMessage& l_type, Observer* l_observer);

		void dispatch(const Message& l_msg);

	private:
		Subscriptions communicators_;

	};

}