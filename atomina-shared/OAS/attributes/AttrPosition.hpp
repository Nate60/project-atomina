#pragma once
#include "core/api.hpp"
#include "OAS/Attribute.hpp"
#include "OAS/AttrBase.hpp"

namespace ATMA
{

    /**
     * Attribute that holds an object's position members 
     */
    class ATMA_API AttrPosition: public AttrBase
    {
    public:

        //default constructor
        AttrPosition();

        //deconstructor
        ~AttrPosition();

        // friend function to output attributes
        friend std::stringstream &operator>>(std::stringstream &l_stream, AttrBase &b);

        /**
         * fill attribute members with data contained within a string stream
         * @param l_stream string stream containing data of the attribute members
         */
        void readIn(std::stringstream &l_stream);

        float m_x, m_y;
    };

}