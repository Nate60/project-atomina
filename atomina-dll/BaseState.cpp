#include "pch.h"
#include "BaseState.h"


namespace ATMA {
	

	BaseState::BaseState() : m_communicable(false), m_transcendent(false), m_transparent(false)
	{

	}

	BaseState::BaseState(BaseState &&b) noexcept: m_communicable(b.m_communicable), m_transcendent(b.m_transcendent), m_transparent(b.m_transparent), m_view(b.m_view)
	{

	}

	BaseState::~BaseState()
	{
		ATMA_ENGINE_INFO("Unspecified State Destroyed");
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