#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "Attribute.hpp"

namespace ATMA
{

    using AttributeType = unsigned int;

    class ATMA_API AttrBase
    {
    public:
        const std::string m_attrTypeName;

        AttrBase(const AttributeType &l_type, const std::string &l_typeName):
            m_type(l_type),
            m_attrTypeName(l_typeName)
        {
        }

        virtual ~AttrBase() {}

        AttributeType getType() const;

        // friend function to output attributes
        friend std::stringstream &operator>>(std::stringstream &l_stream, AttrBase &b);

        virtual void readIn(std::stringstream &l_stream) = 0;
    protected:
        AttributeType m_type;
    };

}