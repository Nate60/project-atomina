#pragma once
#include "core/api.hpp"
#include "OAS/Attribute.hpp"
#include "OAS/AttrBase.hpp"
#include "math/Vec2.hpp"

namespace ATMA
{

    /**
     * Attribute that holds an object's position members
     */
    class ATMA_API AttrShape: public AttrBase
    {
    public:
        // default constructor
        AttrShape();

        // deconstructor
        virtual ~AttrShape();

        // friend function to output attributes
        friend std::stringstream &operator>>(std::stringstream &l_stream, AttrBase &b);

        /**
         * fill attribute members with data contained within a string stream
         * @param l_stream string stream containing data of the attribute members
         */
        void readIn(std::stringstream &l_stream);

        Vec2<float> m_pos{};
        Vec2<float> m_size{};
        float m_rot{};
    };

}