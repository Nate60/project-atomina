#include "pch.h"
#include "SoundManager.h"

namespace ATMA
{

	SoundManager::SoundManager()
	{}

	SoundManager::~SoundManager()
	{}

	void SoundManager::onStateCreate(const StateType &l_type)
	{}

	void SoundManager::onStateChange(const StateType &l_type)
	{}

	void SoundManager::onStateRemove(const StateType &l_type)
	{}

	void SoundManager::update(float l_dt)
	{}

	SoundId SoundManager::play(const std::string &l_sound, const sf::Vector3f &l_pos, bool l_loop, bool l_relative)
	{
		return SoundId();
	}

	bool SoundManager::play(const SoundId &l_id)
	{
		return false;
	}

	bool SoundManager::stop(const SoundId &l_id)
	{
		return false;
	}

	bool SoundManager::pause(const SoundId &l_id)
	{
		return false;
	}

}

