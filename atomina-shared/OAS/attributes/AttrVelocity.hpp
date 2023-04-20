#pragma once
#include "core/api.hpp"
#include "OAS/Attribute.hpp"
#include "OAS/AttrBase.hpp"
#include "math/Vec2.hpp"

namespace ATMA
{

    /**
     * An Attribute that holds velocity members of an object
     */
    class ATMA_API AttrVelocity: public AttrBase
    {
    public:
        // default constructor
        AttrVelocity();

        // deconstructor
        virtual ~AttrVelocity();

        // friend function to output attributes
        friend std::stringstream &operator>>(std::stringstream &l_stream, AttrBase &b);

        /**
         * fill attribute members with data contained within a string stream
         * @param l_stream string stream containing data of the attribute members
         */
        void readIn(std::stringstream &l_stream);

        Vec2<float> m_dpos{}, m_dsize{}, m_drot{};
    };

}