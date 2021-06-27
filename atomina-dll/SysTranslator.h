#include "SysBase.h"
#include "System.h"
#include "AttrTranslatable.h"
#include "Attribute.h"
#include "api.h"

namespace ATMA {
	
	class ATMA_API SysTranslator : public SysBase {
	public:
		SysTranslator(const System& l_type, SystemManager* l_sysMan);

		~SysTranslator();

		void notify(const Message& l_message);

		void update(float l_dt);

	};

}