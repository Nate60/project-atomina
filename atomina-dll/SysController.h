#pragma once
#include "pch.h"
#include "api.h"
#include "SysBase.h"
#include "AttrTranslatable.h"

namespace ATMA
{

	class ATMA_API SysController: public SysBase
	{
	public:
		SysController(const SystemType &l_type, SystemManager &l_sysMan): SysBase(l_type, l_sysMan)
		{
			m_req.set(1);
			m_req.set(3);
		}

		virtual void update(float l_dt) override;

		virtual void handleEvent(const ObjectId &l_id, Event &l_event) override;
	
		virtual void notify(const Message &l_message) override;

	};

}
