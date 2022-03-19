#pragma once
#include "api.h"
#include "Observer.h"

namespace ATMA {

	class ATMA_API Communicator {

	public:
		virtual ~Communicator();

		bool addOverserver(std::shared_ptr<Observer> l_observer);

		bool removeObserver(std::shared_ptr<Observer> l_observer);

		bool hasObserver(const std::shared_ptr<Observer> l_observer) const;

		void broadcast(const Message& l_msg);


	private:
		std::vector<std::shared_ptr<Observer>> m_observers;

	};

}