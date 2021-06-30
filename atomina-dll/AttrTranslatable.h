#pragma once
#include "api.h"
#include "Attribute.h"
#include "AttrBase.h"


namespace ATMA {

	class ATMA_API AttrTranslatable : public AttrBase {
	public:

		AttrTranslatable();

		~AttrTranslatable();

		//friend function to output attributes 
		friend std::stringstream& operator >> (std::stringstream& l_stream, AttrBase& b);


		void readIn(std::stringstream& l_stream);


		float x_, y_, dx_, dy_;
	protected:
		Attribute type_;
	};

}