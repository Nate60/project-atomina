#include "../../pch.hpp"
#include "../../core/api.hpp"
#include "../SysBase.hpp"
#include "../attributes/AttrTranslatable.hpp"
#include "../attributes/AttrDrawable.hpp"

namespace ATMA
{

	class ATMA_API SysRenderer: public SysBase, public sf::Drawable
	{
	public:
		SysRenderer(const SystemType &l_type, SystemManager &l_sysMan): SysBase(l_type, l_sysMan)
		{
			m_req.set(1);
			m_req.set(2);
		}

		virtual void update(float l_dt) override;

		virtual void handleEvent(const ObjectId &l_id, Event &l_event) override;

		virtual void notify(const Message &l_message);

		virtual void draw(sf::RenderTarget &target, const sf::RenderStates &l_states = sf::RenderStates::Default) const override;

	};

}