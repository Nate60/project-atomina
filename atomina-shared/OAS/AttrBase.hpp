#pragma once
#include "../pch.hpp"
#include "../core/api.hpp"
#include "Attribute.hpp"


namespace ATMA {

	using AttributeType = unsigned int;

	class  ATMA_API AttrBase {
	public:
		AttrBase(const AttributeType &l_type) :m_type(l_type) {

		}

		virtual ~AttrBase() {

		}

		AttributeType getType() const;

		//friend function to output attributes 
		friend std::stringstream& operator >> (std::stringstream &l_stream, AttrBase &b);


		virtual void readIn(std::stringstream &l_stream) = 0;

	protected:
		AttributeType m_type;

	};

}