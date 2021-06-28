#pragma once
#include "api.h"
#include "Observer.h"

namespace ATMA {

	class ATMA_API Communicator {

	public:
		virtual ~Communicator();

		bool addOverserver(Observer* l_observer);

		bool removeObserver(Observer* l_observer);

		bool hasObserver(const Observer* l_observer) const;

		void broadcast(const Message& l_msg);


	private:
		std::vector<Observer*> observers_;

	};

}