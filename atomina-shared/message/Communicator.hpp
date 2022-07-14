#pragma once
#include "../core/api.hpp"
#include "Observer.hpp"

namespace ATMA {

	class ATMA_API Communicator {

	public:
		virtual ~Communicator()
		{}

		void addOverserver(std::shared_ptr<Observer> l_observer);

		void removeObserver(std::shared_ptr<Observer> l_observer);

		bool hasObserver(const std::shared_ptr<Observer> l_observer) const;

		void broadcast(const Message& l_msg);


	private:
		std::vector<std::shared_ptr<Observer>> m_observers;

	};

}