#pragma once
#include "core/api.hpp"
#include "OAS/Attribute.hpp"
#include "OAS/AttrBase.hpp"
#include "render/GLText.hpp"

namespace ATMA
{

    /**
     * An Attribute that holds the members of an object required to render text to a display
     */
    class AttrText: public AttrBase
    {
    public:

        // default constructor
        AttrText();

        // deconstructor
        virtual ~AttrText();

        // friend function to output attributes
        friend std::stringstream &operator>>(std::stringstream &l_stream, AttrBase &b);

        /**
         * fill attribute members with data contained within a string stream
         * @param l_stream string stream containing data of the attribute members
         */
        void readIn(std::stringstream &l_stream);

        std::shared_ptr<GLText> m_self = GLText::makeText();
      
    };

}