#include "pch.h"
#include "SysBase.h"
#include "System.h"
#include "AttrTranslatable.h"
#include "Attribute.h"
#include "api.h"

namespace ATMA {
	
	class ATMA_API SysTranslator : public SysBase {
	public:
		SysTranslator(const SystemType& l_type, SystemManager &l_man);

		~SysTranslator();

		void notify(const Message& l_message);

		void update(float l_dt) override;
		
		void handleEvent(const ObjectId &l_obj, Event &l_id) override;

	};

}