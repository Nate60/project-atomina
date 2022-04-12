#include "pch.h"
#include "api.h"
#include "StateSensitive.h"
#include "SoundProperties.h"

namespace ATMA
{

	using SoundId = unsigned int;

	class ATMA_API SoundManager: public StateSensitive
	{
	public:
		SoundManager();
		~SoundManager();

		virtual void onStateCreate(const StateType &l_type) override;
		virtual void onStateChange(const StateType &l_type) override;
		virtual void onStateRemove(const StateType &l_type) override;

		void update(float l_dt);

		SoundId play(const std::string &l_sound, const sf::Vector3f &l_pos, bool l_loop = false, bool l_relative = false);
		bool play(const SoundId &l_id);
		bool stop(const SoundId &l_id);
		bool pause(const SoundId &l_id);

	};

}