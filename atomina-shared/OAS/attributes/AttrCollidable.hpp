#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/AttrBase.hpp"
#include "math/Vec2.hpp"
#include "math/Stadium.hpp"

namespace ATMA
{
    /**
     * Attribute that holds the collider shape for an object
     */
    class AttrCollidable: public AttrBase
    {
    public:
        AttrCollidable();

        virtual ~AttrCollidable();

        /**
         * fill attribute members with data contained within a string stream
         * @param l_stream string stream containing data of the attribute members
         */
        void readIn(std::stringstream &l_stream) override;

        Stadium<float> m_collider{};
    protected:
    };

}