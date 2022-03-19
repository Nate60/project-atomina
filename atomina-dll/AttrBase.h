#pragma once
#include "api.h"
#include "Attribute.h"


namespace ATMA {

	class  ATMA_API AttrBase {
	public:
		AttrBase(const Attribute& l_type) :m_type(l_type) {

		}

		virtual ~AttrBase() {

		}

		Attribute getType() const;

		//friend function to output attributes 
		friend std::stringstream& operator >> (std::stringstream& l_stream, AttrBase& b);


		virtual void readIn(std::stringstream& l_stream) = 0;

	protected:
		Attribute m_type;

	};

}