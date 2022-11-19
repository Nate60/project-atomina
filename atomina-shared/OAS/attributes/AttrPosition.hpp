#pragma once
#include "core/api.hpp"
#include "OAS/Attribute.hpp"
#include "OAS/AttrBase.hpp"

namespace ATMA
{

    class ATMA_API AttrPosition: public AttrBase
    {
    public:
        AttrPosition();

        ~AttrPosition();

        // friend function to output attributes
        friend std::stringstream &operator>>(std::stringstream &l_stream, AttrBase &b);

        void readIn(std::stringstream &l_stream);

        float m_x, m_y;
    };

}