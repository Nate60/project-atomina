#include "../pch.hpp"
#include "Communicator.hpp"

void ATMA::Communicator::addOverserver(std::shared_ptr<Observer> l_observer)
{
    m_observers.push_back(l_observer);
}

void ATMA::Communicator::removeObserver(std::shared_ptr<Observer> l_observer)
{

}

bool ATMA::Communicator::hasObserver(const std::shared_ptr<Observer> l_observer) const
{
    return false;
}

void ATMA::Communicator::broadcast(const Message &l_msg)
{}
