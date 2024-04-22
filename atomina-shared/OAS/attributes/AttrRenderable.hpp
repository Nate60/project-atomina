#pragma once
#include "core/api.hpp"
#include "OAS/Attribute.hpp"
#include "OAS/AttrBase.hpp"
#include "render/GLRenderable.hpp"

namespace ATMA
{

    /**
     * An Attribute that holds velocity members of an object
     */
    class ATMA_API AttrRenderable: public AttrBase, public GLRenderable
    {
    public:
        // default constructor
        AttrRenderable();

        // deconstructor
        virtual ~AttrRenderable();

        // friend function to output attributes
        friend std::stringstream &operator>>(std::stringstream &l_stream, AttrBase &b);

        /**
         * fill attribute members with data contained within a string stream
         * @param l_stream string stream containing data of the attribute members
         */
        void readIn(std::stringstream &l_stream);

      
    };

}