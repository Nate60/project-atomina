#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/AttrBase.hpp"

namespace ATMA
{

    /**
     * Attribute that holds no members but is used as a tag for controller system
     */
    class ATMA_API AttrControllable: public AttrBase
    {
    public:
        // default constructor
        AttrControllable();

        // deconstructor
        ~AttrControllable();

        /**
         * fill attribute members with data contained within a string stream
         * @param l_stream string stream containing data of the attribute members
         */
        void readIn(std::stringstream &l_stream) override;
    };

}
