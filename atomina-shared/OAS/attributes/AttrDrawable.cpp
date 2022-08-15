#include "pch.hpp"
#include "AttrDrawable.hpp"

namespace ATMA
{

    AttrDrawable::AttrDrawable(): AttrBase(AttrType(ATMA::Attribute::Drawable)) {}

    AttrDrawable::~AttrDrawable() {}

    void AttrDrawable::updateScreenPosition(const float &l_x, const float &l_y)
    {
        m_sprite.setPosition(sf::Vector2f{l_x, l_y});
    }

    void AttrDrawable::draw(sf::RenderTarget &l_target, const sf::RenderStates &l_states) const
    {
        l_target.draw(m_sprite, l_states);
    }

    void AttrDrawable::readIn(std::stringstream &l_stream) {}

}
