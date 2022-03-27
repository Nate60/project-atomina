#include "pch.h"
#include "BaseState.h"


namespace ATMA {
	

	BaseState::BaseState(StateManager &l_stateMan) : m_communicable(false), m_transcendent(false), m_transparent(false), m_stateMan(l_stateMan)
	{

	}

	BaseState::BaseState(BaseState &&b) noexcept: m_communicable(b.m_communicable), m_transcendent(b.m_transcendent), m_transparent(b.m_transparent), m_view(b.m_view), m_stateMan(b.m_stateMan)
	{

	}

	BaseState::~BaseState()
	{

	}

	
	bool BaseState::operator==(const BaseState &b) const
	{
		return this->getId() == b.getId();
	}

	bool BaseState::operator<(const BaseState &b) const
	{
		return this->getId() < b.getId();
	}

	bool BaseState::operator>(const BaseState &b) const
	{
		return this->getId() > b.getId();
	}

	sf::View &BaseState::getView()
	{
		return m_view;
	}




}