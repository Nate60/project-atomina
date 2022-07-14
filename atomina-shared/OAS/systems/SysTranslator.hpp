#include "../../pch.hpp"
#include "../SysBase.hpp"
#include "../System.hpp"
#include "../attributes/AttrTranslatable.hpp"
#include "../Attribute.hpp"
#include "../../core/api.hpp"

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