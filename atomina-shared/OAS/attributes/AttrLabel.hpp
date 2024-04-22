#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/AttrBase.hpp"
#include "math/Vec2.hpp"

namespace ATMA
{

    class ATMA_API AttrLabel: public AttrBase
    {
    public:
            // default constructor
        AttrLabel();

        // deconstructor
        virtual ~AttrLabel();

        // friend function to output attributes
        friend std::stringstream &operator>>(std::stringstream &l_stream, AttrBase &b);

        /**
         * fill attribute members with data contained within a string stream
         * @param l_stream string stream containing data of the attribute members
         */
        void readIn(std::stringstream &l_stream);

        std::string m_text;
        Vec2<float> m_pos{};
        Vec2<float> m_size{};
        float m_rot{};
    };

}