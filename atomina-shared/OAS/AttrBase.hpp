#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "Attribute.hpp"

namespace ATMA
{

    using AttributeType = unsigned int;

    /**
     * Super class for attribute, which define behaviours
     * of objects registering in the context
     */
    class AttrBase
    {
    public:
        const std::string m_attrTypeName;

        // constructor specifying attribute type id and name
        AttrBase(const AttributeType &l_type, const std::string &l_typeName): m_type(l_type), m_attrTypeName(l_typeName)
        {
        }

        // deconstructor
        virtual ~AttrBase() {}

        /**
         * gives the type id of the attribute
         * @returns Attribute type enum of the attribute
         */
        AttributeType getType() const;

        // friend function to output attributes
        friend std::stringstream &operator>>(std::stringstream &l_stream, AttrBase &b);

        /**
         * deserialization from string stream
         * @param l_stream string stream containing attribute definition
         */
        virtual void readIn(std::stringstream &l_stream) = 0;
    protected:
        AttributeType m_type;
    };

    inline std::ostream &operator<<(std::ostream &os, const AttrBase &attr)
    {
        return os << attr.m_attrTypeName;
    }
}