#pragma once
#include "../../pch.hpp"
#include "../SysBase.hpp"
#include "../System.hpp"
#include "../attributes/AttrTranslatable.hpp"
#include "../Attribute.hpp"
#include "../../core/api.hpp"

namespace ATMA {
	
	class ATMA_API SysTranslator : public SysBase {
	public:
		SysTranslator();

		~SysTranslator();

		void update(const float &l_dt) override;

	};

}