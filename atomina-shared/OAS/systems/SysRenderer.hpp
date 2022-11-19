#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/attributes/AttrGraphic.hpp"
#include "OAS/System.hpp"

namespace ATMA
{

    class ATMA_API SysRenderer: public SysBase, public sf::Drawable
    {
    public:
        SysRenderer();

        virtual void update(const float &l_dt) override;

        virtual void draw(
            sf::RenderTarget &target,
            const sf::RenderStates &l_states = sf::RenderStates::Default
        ) const override;

        virtual void notify(const ObjectEventContext &l_e) override;
    };

}