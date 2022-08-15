#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/AttrBase.hpp"

namespace ATMA
{

    class ATMA_API AttrDrawable: public AttrBase, sf::Drawable
    {
    public:
        AttrDrawable();
        ~AttrDrawable();

        virtual void updateScreenPosition(const float &l_x, const float &l_y);
        virtual void draw(sf::RenderTarget &l_target, const sf::RenderStates &l_states)
            const override;
        virtual void readIn(std::stringstream &l_stream) override;

        sf::Sprite m_sprite{};
    };

}