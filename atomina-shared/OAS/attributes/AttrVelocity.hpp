#pragma once
#include "core/api.hpp"
#include "OAS/Attribute.hpp"
#include "OAS/AttrBase.hpp"

namespace ATMA
{

    class ATMA_API AttrVelocity: public AttrBase
    {
    public:
        AttrVelocity();

        ~AttrVelocity();

        // friend function to output attributes
        friend std::stringstream &operator>>(std::stringstream &l_stream, AttrBase &b);

        void readIn(std::stringstream &l_stream);

        float m_dx, m_dy;
    };

}